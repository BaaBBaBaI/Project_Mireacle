#pragma once
#include <string>

class Config {
private:
    int port = 8080;
    int threadPoolSize = 16;
    size_t cacheLimitMb = 50;
    std::string policy = "LRU";

public:
    Config() = default;
    explicit Config(const std::string& filepath);

    bool loadFromFile(const std::string& filepath);

    int getPort() const { return port; }
    int getThreadPoolSize() const { return threadPoolSize; }
    size_t getCacheLimitMb() const { return cacheLimitMb; }
    std::string getPolicy() const { return policy; }

    void setPort(int p) { port = p; }
    void setThreadPoolSize(int t) { threadPoolSize = t; }
    void setCacheLimitMb(size_t limit) { cacheLimitMb = limit; }
    void setPolicy(const std::string& pol) { policy = pol; }
};
