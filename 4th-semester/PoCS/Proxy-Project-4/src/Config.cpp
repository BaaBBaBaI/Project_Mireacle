#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

static std::string trim(const std::string& str) {
    auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

Config::Config(const std::string& filepath) {
    loadFromFile(filepath);
}

bool Config::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[CONFIG] Could not open config file: " << filepath << ". Using defaults." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) {
            continue;
        }

        std::string key = trim(line.substr(0, delimiterPos));
        std::string val = trim(line.substr(delimiterPos + 1));

        if (key == "port") {
            try {
                port = std::stoi(val);
            } catch (...) {}
        } else if (key == "threads") {
            try {
                int parsed = std::stoi(val);
                if (parsed > 0) {
                    threadPoolSize = parsed;
                }
            } catch (...) {}
        } else if (key == "cache_limit_mb") {
            try {
                cacheLimitMb = std::stoull(val);
            } catch (...) {}
        } else if (key == "policy") {
            policy = val;
        }
    }
    return true;
}
