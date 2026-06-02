#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

static std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Logger::info(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "[" << getTimestamp() << "] [THREAD-" << std::this_thread::get_id() 
              << "] [INFO] " << message << std::endl;
}

void Logger::warn(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "[" << getTimestamp() << "] [THREAD-" << std::this_thread::get_id() 
              << "] [WARN] " << message << std::endl;
}

void Logger::error(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cerr << "[" << getTimestamp() << "] [THREAD-" << std::this_thread::get_id() 
              << "] [ERROR] " << message << std::endl;
}

void Logger::logRequest(const std::string& clientIp, const std::string& method, const std::string& url, const std::string& status, const std::string& extra) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "[" << getTimestamp() << "] [THREAD-" << std::this_thread::get_id() 
              << "] [" << status << "] Client: " << clientIp << " | " << method << " " << url;
    if (!extra.empty()) {
        std::cout << " (" << extra << ")";
    }
    std::cout << std::endl;
}
