#include "ProxyServer.h"
#include "ConnectionHandler.h"
#include "Logger.h"
#include "CacheManager.h"
#include "LRUPolicy.h"
#include "FIFOPolicy.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

ProxyServer::ProxyServer(const Config& cfg) : config(cfg) {}

ProxyServer::~ProxyServer() {
    stop();
}

void ProxyServer::start() {
    if (running) return;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        Logger::getInstance().error("Failed to create master TCP socket");
        return;
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        Logger::getInstance().error("setsockopt SO_REUSEADDR failed");
        close(serverSocket);
        serverSocket = -1;
        return;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config.getPort());

    if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        Logger::getInstance().error("Failed to bind TCP socket to port " + std::to_string(config.getPort()));
        close(serverSocket);
        serverSocket = -1;
        return;
    }

    if (listen(serverSocket, 128) < 0) {
        Logger::getInstance().error("listen() failed");
        close(serverSocket);
        serverSocket = -1;
        return;
    }

    // Configure CacheManager Strategy Policy
    std::unique_ptr<ICachePolicy> cachePolicy;
    if (config.getPolicy() == "FIFO") {
        cachePolicy = std::make_unique<FIFOPolicy>();
    } else {
        cachePolicy = std::make_unique<LRUPolicy>();
    }
    CacheManager::getInstance().configure(std::move(cachePolicy), config.getCacheLimitMb());

    Logger::getInstance().info("Cache manager initialized with policy: " + CacheManager::getInstance().getPolicyName());
    Logger::getInstance().info("Cache size limit set to: " + std::to_string(CacheManager::getInstance().getMaxSizeMb()) + " MB");

    // Start Thread Pool
    threadPool = std::make_unique<ThreadPool>(config.getThreadPoolSize());
    Logger::getInstance().info("Thread Pool initialized with " + std::to_string(config.getThreadPoolSize()) + " worker threads");

    running = true;
    acceptThread = std::thread(&ProxyServer::listenAndAccept, this);
    Logger::getInstance().info("Corporate Proxy Server successfully started on port " + std::to_string(config.getPort()));
}

void ProxyServer::stop() {
    if (!running) return;

    running = false;
    if (acceptThread.joinable()) {
        acceptThread.join();
    }

    if (serverSocket >= 0) {
        close(serverSocket);
        serverSocket = -1;
    }

    threadPool.reset();
    Logger::getInstance().info("Proxy Server successfully stopped.");
}

void ProxyServer::listenAndAccept() {
    while (running) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(serverSocket, &fds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(serverSocket + 1, &fds, nullptr, nullptr, &timeout);
        if (activity < 0) {
            if (errno == EINTR) continue;
            break;
        }
        if (activity == 0) {
            continue;
        }

        struct sockaddr_in clientAddress;
        socklen_t addrlen = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &addrlen);
        if (clientSocket < 0) {
            if (errno == EINTR) continue;
            continue;
        }

        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), ipStr, INET_ADDRSTRLEN);
        std::string clientIp(ipStr);

        threadPool->enqueue([clientSocket, clientIp]() {
            ConnectionHandler handler(clientSocket, clientIp);
            handler.handle();
        });
    }
}
