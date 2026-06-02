#pragma once
#include <string>
#include "HttpRequest.h"

class ConnectionHandler {
private:
    int clientSocket;
    std::string clientIp;

public:
    ConnectionHandler(int socket, const std::string& ip);
    ~ConnectionHandler();

    void handle();

private:
    void handleGet(const HttpRequest& request);
    void handleConnect(const HttpRequest& request);
    void handlePassThrough(const HttpRequest& request);
    
    void sendResponse(int socket, const std::string& data);
    void sendErrorResponse(int socket, int statusCode, const std::string& statusMessage, const std::string& details);

    std::string readFromSocket(int socket, bool& disconnected);
    void tunnel(int serverSocket);
};
