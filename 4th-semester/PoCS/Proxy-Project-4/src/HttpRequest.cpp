#include "HttpRequest.h"
#include <sstream>
#include <algorithm>

static std::string trimString(const std::string& str) {
    auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

bool HttpRequest::parse(const std::string& rawRequest) {
    isValid = false;
    if (rawRequest.empty()) return false;

    size_t headerEnd = rawRequest.find("\r\n\r\n");
    size_t headerDelimiterLen = 4;
    if (headerEnd == std::string::npos) {
        headerEnd = rawRequest.find("\n\n");
        headerDelimiterLen = 2;
    }
    if (headerEnd == std::string::npos) {
        headerEnd = rawRequest.size();
        headerDelimiterLen = 0;
    }

    std::string headerPart = rawRequest.substr(0, headerEnd);
    if (headerDelimiterLen > 0 && headerEnd + headerDelimiterLen < rawRequest.size()) {
        body = rawRequest.substr(headerEnd + headerDelimiterLen);
    } else {
        body = "";
    }

    std::istringstream stream(headerPart);
    std::string requestLine;
    if (!std::getline(stream, requestLine)) {
        return false;
    }

    requestLine = trimString(requestLine);
    std::istringstream reqLineStream(requestLine);
    if (!(reqLineStream >> method >> url >> version)) {
        return false;
    }

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

    if (method == "CONNECT") {
        size_t colon = url.find(':');
        if (colon != std::string::npos) {
            host = url.substr(0, colon);
            try {
                port = std::stoi(url.substr(colon + 1));
            } catch (...) {
                port = 443;
            }
        } else {
            host = url;
            port = 443;
        }
    } else {
        size_t schemaPos = url.find("://");
        if (schemaPos != std::string::npos) {
            size_t hostStart = schemaPos + 3;
            size_t hostEnd = url.find('/', hostStart);
            std::string hostPortStr;
            if (hostEnd == std::string::npos) {
                hostPortStr = url.substr(hostStart);
            } else {
                hostPortStr = url.substr(hostStart, hostEnd - hostStart);
            }

            size_t colon = hostPortStr.find(':');
            if (colon != std::string::npos) {
                host = hostPortStr.substr(0, colon);
                try {
                    port = std::stoi(hostPortStr.substr(colon + 1));
                } catch (...) {
                    port = 80;
                }
            } else {
                host = hostPortStr;
                port = 80;
            }
        } else {
            std::string hostHeader = getHeader("host");
            if (!hostHeader.empty()) {
                size_t colon = hostHeader.find(':');
                if (colon != std::string::npos) {
                    host = hostHeader.substr(0, colon);
                    try {
                        port = std::stoi(hostHeader.substr(colon + 1));
                    } catch (...) {
                        port = 80;
                    }
                } else {
                    host = hostHeader;
                    port = 80;
                }
            } else {
                return false;
            }
        }
    }

    isValid = true;
    return true;
}

std::string HttpRequest::getHeader(const std::string& name) const {
    std::string nameLower = name;
    std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
    auto it = headers.find(nameLower);
    if (it != headers.end()) {
        return it->second;
    }
    return "";
}

std::string HttpRequest::toRawString() const {
    std::stringstream ss;
    std::string path = url;
    size_t schemaPos = url.find("://");
    if (schemaPos != std::string::npos) {
        size_t hostStart = schemaPos + 3;
        size_t firstSlash = url.find('/', hostStart);
        if (firstSlash != std::string::npos) {
            path = url.substr(firstSlash);
        } else {
            path = "/";
        }
    }

    ss << method << " " << path << " " << version << "\r\n";
    for (const auto& pair : headers) {
        if (pair.first == "connection") {
            ss << "connection: close\r\n";
        } else if (pair.first == "proxy-connection") {
            continue;
        } else {
            ss << pair.first << ": " << pair.second << "\r\n";
        }
    }
    if (headers.find("connection") == headers.end()) {
        ss << "connection: close\r\n";
    }
    ss << "\r\n";
    if (!body.empty()) {
        ss << body;
    }
    return ss.str();
}
