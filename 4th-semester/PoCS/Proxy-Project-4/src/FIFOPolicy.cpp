#include "FIFOPolicy.h"

void FIFOPolicy::touch(const std::string& key) {
    (void)key;
}

void FIFOPolicy::insert(const std::string& key, size_t size) {
    (void)size;
    erase(key);
    fifoList.push_back(key);
    fifoMap[key] = std::prev(fifoList.end());
}

void FIFOPolicy::erase(const std::string& key) {
    auto it = fifoMap.find(key);
    if (it != fifoMap.end()) {
        fifoList.erase(it->second);
        fifoMap.erase(it);
    }
}

std::string FIFOPolicy::getCandidateToEvict() {
    if (fifoList.empty()) {
        return "";
    }
    std::string key = fifoList.front();
    fifoMap.erase(key);
    fifoList.pop_front();
    return key;
}
