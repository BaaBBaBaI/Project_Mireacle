#pragma once
#include <string>
#include <unordered_map>
#include <shared_mutex>
#include <memory>
#include "ICachePolicy.h"

struct CacheEntry {
    std::string content;
    size_t size;
};

class CacheManager {
private:
    std::unordered_map<std::string, CacheEntry> cacheStorage;
    std::unique_ptr<ICachePolicy> policy;
    size_t currentSize = 0;
    size_t maxSizeMb = 50;
    
    mutable std::shared_mutex cacheMutex;

    CacheManager();

public:
    CacheManager(const CacheManager&) = delete;
    CacheManager& operator=(const CacheManager&) = delete;

    static CacheManager& getInstance();

    void configure(std::unique_ptr<ICachePolicy> newPolicy, size_t maxMb);
    void setLimit(size_t mb);
    void clear();

    bool get(const std::string& url, std::string& out_content);
    void put(const std::string& url, const std::string& content);

    size_t getCurrentSize() const;
    size_t getMaxSizeMb() const;
    size_t getEntryCount() const;
    std::string getPolicyName() const;

private:
    void evictToFit(size_t neededBytes);
};
