#pragma once
#include <string>
#include <mutex>
#include <unordered_map>

class CacheManager {
private:
    std::unordered_map<std::string, std::string> cacheStorage;
    std::mutex cacheMutex;


    CacheManager() = default;
public:
    CacheManager(const CacheManager&) = delete;
    CacheManager& operator=(const CacheManager&) = delete;

    static CacheManager& getInstance();

    bool get(const std::string& url, std::string& out_content);
    void put(const std::string& url, const std::string& content);
};