#include "ConnectionHandler.h"
#include "CacheManager.h"
#include "Logger.h"
#include "HttpResponse.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

ConnectionHandler::ConnectionHandler(int socket, const std::string& ip) 
    : clientSocket(socket), clientIp(ip) {}

ConnectionHandler::~ConnectionHandler() {
    if (clientSocket >= 0) {
        close(clientSocket);
    }
}

void ConnectionHandler::handle() {
    bool disconnected = false;
    std::string rawRequest = readFromSocket(clientSocket, disconnected);
    
    if (rawRequest.empty()) {
        return;
    }

    HttpRequest request;
    if (!request.parse(rawRequest)) {
        sendErrorResponse(clientSocket, 400, "Bad Request", "Malformed HTTP request");
        return;
    }

    if (request.getMethod() == "CONNECT") {
        handleConnect(request);
    } else if (request.getMethod() == "GET") {
        handleGet(request);
    } else {
        handlePassThrough(request);
    }
}

void ConnectionHandler::handleConnect(const HttpRequest& request) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    std::string portStr = std::to_string(request.getPort());
    int s = getaddrinfo(request.getHost().c_str(), portStr.c_str(), &hints, &res);
    if (s != 0) {
        Logger::getInstance().error("CONNECT DNS resolution failed for " + request.getHost());
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "DNS resolution failed");
        return;
    }

    int serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (serverSocket < 0) {
        freeaddrinfo(res);
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "Target socket creation failed");
        return;
    }

    if (connect(serverSocket, res->ai_addr, res->ai_addrlen) < 0) {
        close(serverSocket);
        freeaddrinfo(res);
        Logger::getInstance().error("CONNECT failed to connect to " + request.getHost() + ":" + portStr);
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "Connection to destination failed");
        return;
    }
    freeaddrinfo(res);

    sendResponse(clientSocket, "HTTP/1.1 200 Connection Established\r\n\r\n");
    
    tunnel(serverSocket);
    close(serverSocket);
}

void ConnectionHandler::tunnel(int serverSocket) {
    char buffer[8192];
    Logger::getInstance().logRequest(clientIp, "CONNECT", "Tunnel to remote host", "TUNNEL");

    while (true) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(clientSocket, &fds);
        FD_SET(serverSocket, &fds);
        int maxFd = std::max(clientSocket, serverSocket);

        int activity = select(maxFd + 1, &fds, nullptr, nullptr, nullptr);
        if (activity < 0) {
            if (errno == EINTR) continue;
            break;
        }

        if (FD_ISSET(clientSocket, &fds)) {
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) break;
            ssize_t bytesSent = send(serverSocket, buffer, bytesRead, 0);
            if (bytesSent <= 0) break;
        }

        if (FD_ISSET(serverSocket, &fds)) {
            ssize_t bytesRead = recv(serverSocket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) break;
            ssize_t bytesSent = send(clientSocket, buffer, bytesRead, 0);
            if (bytesSent <= 0) break;
        }
    }
}

void ConnectionHandler::handleGet(const HttpRequest& request) {
    std::string cachedResponse;
    if (CacheManager::getInstance().get(request.getUrl(), cachedResponse)) {
        Logger::getInstance().logRequest(clientIp, "GET", request.getUrl(), "HIT");
        sendResponse(clientSocket, cachedResponse);
        return;
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    std::string portStr = std::to_string(request.getPort());
    int s = getaddrinfo(request.getHost().c_str(), portStr.c_str(), &hints, &res);
    if (s != 0) {
        Logger::getInstance().logRequest(clientIp, "GET", request.getUrl(), "MISS", "DNS resolution failed");
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "DNS resolution failed");
        return;
    }

    int serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (serverSocket < 0) {
        freeaddrinfo(res);
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "Socket creation failed");
        return;
    }

    if (connect(serverSocket, res->ai_addr, res->ai_addrlen) < 0) {
        close(serverSocket);
        freeaddrinfo(res);
        Logger::getInstance().logRequest(clientIp, "GET", request.getUrl(), "MISS", "Connection to remote failed");
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "Connection to destination failed");
        return;
    }
    freeaddrinfo(res);

    std::string rawForward = request.toRawString();
    sendResponse(serverSocket, rawForward);

    std::string fullResponse;
    char buffer[8192];
    while (true) {
        ssize_t bytesRead = recv(serverSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            if (errno == EINTR) continue;
            break;
        }
        if (bytesRead == 0) {
            break;
        }
        fullResponse.append(buffer, bytesRead);
    }
    close(serverSocket);

    HttpResponse response;
    bool parsed = response.parse(fullResponse);
    std::string logStatus = "Status: ";
    if (parsed) {
        logStatus += std::to_string(response.getStatusCode());
    } else {
        logStatus += "Invalid Response";
    }

    Logger::getInstance().logRequest(clientIp, "GET", request.getUrl(), "MISS", logStatus);

    if (parsed && response.isCacheable()) {
        CacheManager::getInstance().put(request.getUrl(), fullResponse);
    }

    sendResponse(clientSocket, fullResponse);
}

void ConnectionHandler::handlePassThrough(const HttpRequest& request) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    std::string portStr = std::to_string(request.getPort());
    int s = getaddrinfo(request.getHost().c_str(), portStr.c_str(), &hints, &res);
    if (s != 0) {
        Logger::getInstance().logRequest(clientIp, request.getMethod(), request.getUrl(), "PASS", "DNS resolution failed");
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "DNS resolution failed");
        return;
    }

    int serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (serverSocket < 0) {
        freeaddrinfo(res);
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "Socket creation failed");
        return;
    }

    if (connect(serverSocket, res->ai_addr, res->ai_addrlen) < 0) {
        close(serverSocket);
        freeaddrinfo(res);
        Logger::getInstance().logRequest(clientIp, request.getMethod(), request.getUrl(), "PASS", "Connection failed");
        sendErrorResponse(clientSocket, 502, "Bad Gateway", "Connection to destination failed");
        return;
    }
    freeaddrinfo(res);

    std::string rawForward = request.toRawString();
    sendResponse(serverSocket, rawForward);

    std::string fullResponse;
    char buffer[8192];
    while (true) {
        ssize_t bytesRead = recv(serverSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            if (errno == EINTR) continue;
            break;
        }
        if (bytesRead == 0) {
            break;
        }
        fullResponse.append(buffer, bytesRead);
    }
    close(serverSocket);

    Logger::getInstance().logRequest(clientIp, request.getMethod(), request.getUrl(), "PASS");
    sendResponse(clientSocket, fullResponse);
}

void ConnectionHandler::sendResponse(int socket, const std::string& data) {
    size_t totalSent = 0;
    while (totalSent < data.size()) {
        ssize_t sent = send(socket, data.data() + totalSent, data.size() - totalSent, 0);
        if (sent <= 0) {
            if (sent < 0 && errno == EINTR) continue;
            break;
        }
        totalSent += sent;
    }
}

void ConnectionHandler::sendErrorResponse(int socket, int statusCode, const std::string& statusMessage, const std::string& details) {
    std::stringstream ss;
    ss << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n"
       << "Content-Type: text/html\r\n"
       << "Connection: close\r\n"
       << "Content-Length: " << (100 + statusMessage.size() + details.size()) << "\r\n\r\n"
       << "<html><head><title>" << statusCode << " " << statusMessage << "</title></head>"
       << "<body><h1>" << statusCode << " " << statusMessage << "</h1>"
       << "<p>" << details << "</p></body></html>";
    sendResponse(socket, ss.str());
}

std::string ConnectionHandler::readFromSocket(int socket, bool& disconnected) {
    std::string data;
    char buffer[4096];
    disconnected = false;

    while (true) {
        ssize_t bytesRead = recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                continue;
            }
            break;
        }
        if (bytesRead == 0) {
            disconnected = true;
            break;
        }
        data.append(buffer, bytesRead);

        if (data.find("\r\n\r\n") != std::string::npos || data.find("\n\n") != std::string::npos) {
            break;
        }
        if (data.size() > 8192) {
            break;
        }
    }
    return data;
}
