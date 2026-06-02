#pragma once
#include "ICachePolicy.h"
#include <list>
#include <unordered_map>

class FIFOPolicy : public ICachePolicy {
private:
    std::list<std::string> fifoList;
    std::unordered_map<std::string, std::list<std::string>::iterator> fifoMap;

public:
    FIFOPolicy() = default;
    ~FIFOPolicy() override = default;

    void touch(const std::string& key) override;
    void insert(const std::string& key, size_t size) override;
    void erase(const std::string& key) override;
    std::string getCandidateToEvict() override;
    std::string getName() const override { return "FIFO"; }
};
