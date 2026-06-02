#pragma once
#include <string>
#include <unordered_map>

class HttpRequest {
private:
    std::string method;
    std::string url;
    std::string version;
    std::string host;
    int port = 80;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    bool isValid = false;

public:
    HttpRequest() = default;
    
    bool parse(const std::string& rawRequest);

    std::string getMethod() const { return method; }
    std::string getUrl() const { return url; }
    std::string getVersion() const { return version; }
    std::string getHost() const { return host; }
    int getPort() const { return port; }
    std::string getHeader(const std::string& name) const;
    std::string getBody() const { return body; }
    bool valid() const { return isValid; }

    std::string toRawString() const;
};
