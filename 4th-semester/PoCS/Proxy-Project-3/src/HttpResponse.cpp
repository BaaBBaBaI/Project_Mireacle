#include "HttpResponse.h"
#include <sstream>
#include <algorithm>

static std::string trimString(const std::string& str) {
    auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

bool HttpResponse::parse(const std::string& rawResponse) {
    isValid = false;
    if (rawResponse.empty()) return false;

    size_t headerEnd = rawResponse.find("\r\n\r\n");
    size_t headerDelimiterLen = 4;
    if (headerEnd == std::string::npos) {
        headerEnd = rawResponse.find("\n\n");
        headerDelimiterLen = 2;
    }
    if (headerEnd == std::string::npos) {
        headerEnd = rawResponse.size();
        headerDelimiterLen = 0;
    }

    std::string headerPart = rawResponse.substr(0, headerEnd);
    if (headerDelimiterLen > 0 && headerEnd + headerDelimiterLen < rawResponse.size()) {
        body = rawResponse.substr(headerEnd + headerDelimiterLen);
    } else {
        body = "";
    }

    std::istringstream stream(headerPart);
    std::string statusLine;
    if (!std::getline(stream, statusLine)) {
        return false;
    }

    statusLine = trimString(statusLine);
    std::istringstream statusLineStream(statusLine);
    if (!(statusLineStream >> version >> statusCode)) {
        return false;
    }
    std::getline(statusLineStream, statusMessage);
    statusMessage = trimString(statusMessage);

    std::string line;
    while (std::getline(stream, line)) {
        line = trimString(line);
        if (line.empty()) continue;
        size_t colon = line.find(':');
        if (colon != std::string::npos) {
            std::string key = trimString(line.substr(0, colon));
            std::string val = trimString(line.substr(colon + 1));
            std::string keyLower = key;
            std::transform(keyLower.begin(), keyLower.end(), keyLower.begin(), ::tolower);
            headers[keyLower] = val;
        }
    }

    isValid = true;
    return true;
}

std::string HttpResponse::getHeader(const std::string& name) const {
    std::string nameLower = name;
    std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
    auto it = headers.find(nameLower);
    if (it != headers.end()) {
        return it->second;
    }
    return "";
}

bool HttpResponse::isCacheable() const {
    if (!isValid) return false;
    if (statusCode != 200) return false;

    std::string cacheControl = getHeader("cache-control");
    if (!cacheControl.empty()) {
        std::transform(cacheControl.begin(), cacheControl.end(), cacheControl.begin(), ::tolower);
        if (cacheControl.find("no-store") != std::string::npos ||
            cacheControl.find("private") != std::string::npos ||
            cacheControl.find("no-cache") != std::string::npos) {
            return false;
        }
    }

    std::string pragma = getHeader("pragma");
    if (!pragma.empty()) {
        std::transform(pragma.begin(), pragma.end(), pragma.begin(), ::tolower);
        if (pragma.find("no-cache") != std::string::npos) {
            return false;
        }
    }

    return true;
}
