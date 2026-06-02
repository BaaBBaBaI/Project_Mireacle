#pragma once
#include "ICachePolicy.h"
#include <list>
#include <unordered_map>

class LRUPolicy : public ICachePolicy {
private:
    std::list<std::string> lruList;
    std::unordered_map<std::string, std::list<std::string>::iterator> lruMap;

public:
    LRUPolicy() = default;
    ~LRUPolicy() override = default;

    void touch(const std::string& key) override;
    void insert(const std::string& key, size_t size) override;
    void erase(const std::string& key) override;
    std::string getCandidateToEvict() override;
    std::string getName() const override { return "LRU"; }
};
