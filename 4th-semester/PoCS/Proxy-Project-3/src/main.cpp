#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <memory>
#include "ProxyServer.h"
#include "Config.h"
#include "Logger.h"

std::unique_ptr<ProxyServer> g_server = nullptr;

void signalHandler(int signum) {
    Logger::getInstance().info("Signal (" + std::to_string(signum) + ") received. Shutting down...");
    if (g_server) {
        g_server->stop();
    }
}

int main() {
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    Logger::getInstance().info("Starting Corporate Caching HTTP Proxy Server daemon...");

    Config config("config.txt");

    g_server = std::make_unique<ProxyServer>(config);
    g_server->start();

    while (g_server && g_server->isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    Logger::getInstance().info("Proxy Server process exited cleanly.");
    return 0;
}
