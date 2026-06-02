#pragma once
#include <string>

class ICachePolicy {
public:
    virtual ~ICachePolicy() = default;
    
    virtual void touch(const std::string& key) = 0;
    virtual void insert(const std::string& key, size_t size) = 0;
    virtual void erase(const std::string& key) = 0;
    virtual std::string getCandidateToEvict() = 0;
    virtual std::string getName() const = 0;
};
