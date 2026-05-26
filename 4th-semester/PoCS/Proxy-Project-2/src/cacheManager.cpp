#include "cacheManager.h"
#include <iostream>

CacheManager& CacheManager::getInstance() {
    static CacheManager instance; 
    return instance;
}

bool CacheManager::get(const std::string& url, std::string& out_content) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    auto it = cacheStorage.find(url);
    if (it != cacheStorage.end()) {
        out_content = it->second;
        std::cout << "[CACHE HIT] URL: " << url << "\n";
        return true;
    }
    std::cout << "[CACHE MISS] URL: " << url << "\n";
    return false;
}

void CacheManager::put(const std::string& url, const std::string& content) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    cacheStorage[url] = content;
    std::cout << "[CACHE PUT] Saved " << content.size() << " bytes for " << url << "\n";
}