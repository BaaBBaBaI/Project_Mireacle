#pragma once
#include <string>
#include <unordered_map>

class HttpResponse {
private:
    std::string version;
    int statusCode = 0;
    std::string statusMessage;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    bool isValid = false;

public:
    HttpResponse() = default;
    
    bool parse(const std::string& rawResponse);

    std::string getVersion() const { return version; }
    int getStatusCode() const { return statusCode; }
    std::string getStatusMessage() const { return statusMessage; }
    std::string getHeader(const std::string& name) const;
    std::string getBody() const { return body; }
    bool valid() const { return isValid; }

    bool isCacheable() const;
};
