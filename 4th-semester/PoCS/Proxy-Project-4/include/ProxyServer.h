#pragma once
#include <string>
#include <memory>
#include <atomic>
#include <thread>
#include "ThreadPool.h"
#include "Config.h"

class ProxyServer {
private:
    Config config;
    int serverSocket = -1;
    std::atomic<bool> running{false};
    std::unique_ptr<ThreadPool> threadPool;
    std::thread acceptThread;

public:
    explicit ProxyServer(const Config& cfg);
    ~ProxyServer();

    void start();
    void stop();

    bool isRunning() const { return running.load(); }
    int getPort() const { return config.getPort(); }

private:
    void listenAndAccept();
};
