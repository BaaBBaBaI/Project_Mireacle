#include "CacheManager.h"
#include "LRUPolicy.h"
#include "FIFOPolicy.h"
#include <iostream>
#include <mutex>

CacheManager::CacheManager() {
    policy = std::make_unique<LRUPolicy>();
}

CacheManager& CacheManager::getInstance() {
    static CacheManager instance;
    return instance;
}

void CacheManager::configure(std::unique_ptr<ICachePolicy> newPolicy, size_t maxMb) {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    policy = std::move(newPolicy);
    maxSizeMb = maxMb;
    cacheStorage.clear();
    currentSize = 0;
}

void CacheManager::setLimit(size_t mb) {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    maxSizeMb = mb;
    evictToFit(0);
}

void CacheManager::clear() {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    cacheStorage.clear();
    if (policy) {
        // Keep policy type but clear its contents
        if (policy->getName() == "FIFO") {
            // Recreate FIFO to clear it
            policy = std::make_unique<FIFOPolicy>();
        } else {
            policy = std::make_unique<LRUPolicy>();
        }
    } else {
        policy = std::make_unique<LRUPolicy>();
    }
    currentSize = 0;
}

bool CacheManager::get(const std::string& url, std::string& out_content) {
    bool found = false;
    {
        std::shared_lock<std::shared_mutex> lock(cacheMutex);
        auto it = cacheStorage.find(url);
        if (it != cacheStorage.end()) {
            out_content = it->second.content;
            found = true;
        }
    }
    if (found) {
        std::unique_lock<std::shared_mutex> lock(cacheMutex);
        if (cacheStorage.find(url) != cacheStorage.end()) {
            policy->touch(url);
        }
    }
    return found;
}

void CacheManager::put(const std::string& url, const std::string& content) {
    std::unique_lock<std::shared_mutex> lock(cacheMutex);
    
    size_t size = content.size();
    size_t limitBytes = maxSizeMb * 1024 * 1024;
    
    if (size > limitBytes) {
        return;
    }
    
    auto it = cacheStorage.find(url);
    if (it != cacheStorage.end()) {
        currentSize -= it->second.size;
    }
    
    evictToFit(size);
    
    cacheStorage[url] = {content, size};
    currentSize += size;
    policy->insert(url, size);
}

void CacheManager::evictToFit(size_t neededBytes) {
    size_t limitBytes = maxSizeMb * 1024 * 1024;
    while (currentSize + neededBytes > limitBytes) {
        std::string victim = policy->getCandidateToEvict();
        if (victim.empty()) {
            break;
        }
        auto it = cacheStorage.find(victim);
        if (it != cacheStorage.end()) {
            currentSize -= it->second.size;
            cacheStorage.erase(it);
        }
    }
}

size_t CacheManager::getCurrentSize() const {
    std::shared_lock<std::shared_mutex> lock(cacheMutex);
    return currentSize;
}

size_t CacheManager::getMaxSizeMb() const {
    std::shared_lock<std::shared_mutex> lock(cacheMutex);
    return maxSizeMb;
}

size_t CacheManager::getEntryCount() const {
    std::shared_lock<std::shared_mutex> lock(cacheMutex);
    return cacheStorage.size();
}

std::string CacheManager::getPolicyName() const {
    std::shared_lock<std::shared_mutex> lock(cacheMutex);
    return policy ? policy->getName() : "None";
}
