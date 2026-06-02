#pragma once
#include <string>
#include <mutex>

class Logger {
private:
    std::mutex logMutex;
    Logger() = default;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void logRequest(const std::string& clientIp, const std::string& method, const std::string& url, const std::string& status, const std::string& extra = "");
};
