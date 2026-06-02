#include "LRUPolicy.h"

void LRUPolicy::touch(const std::string& key) {
    auto it = lruMap.find(key);
    if (it != lruMap.end()) {
        lruList.erase(it->second);
        lruList.push_front(key);
        it->second = lruList.begin();
    }
}

void LRUPolicy::insert(const std::string& key, size_t size) {
    (void)size;
    erase(key);
    lruList.push_front(key);
    lruMap[key] = lruList.begin();
}

void LRUPolicy::erase(const std::string& key) {
    auto it = lruMap.find(key);
    if (it != lruMap.end()) {
        lruList.erase(it->second);
        lruMap.erase(it);
    }
}

std::string LRUPolicy::getCandidateToEvict() {
    if (lruList.empty()) {
        return "";
    }
    std::string key = lruList.back();
    lruMap.erase(key);
    lruList.pop_back();
    return key;
}
