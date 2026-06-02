#include <gtest/gtest.h>
#include "CacheManager.h"
#include "ProxyServer.h"
#include "Config.h"

#include <thread>
#include <vector>
#include <string>
#include <atomic>
#include <chrono>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

// Scenario 1: Classic cache workflow simulated
TEST(ProxyIntegrationScenario, ClassicCacheWorkflow) {
    CacheManager& cache = CacheManager::getInstance();
    cache.clear();

    std::string requested_url = "http://internal-corporate-portal.local/index.html";
    std::string buffer;

    bool first_check = cache.get(requested_url, buffer);
    ASSERT_FALSE(first_check);

    std::string mock_network_response = "HTTP/1.1 200 OK\r\nContent-Length: 23\r\nCache-Control: public\r\n\r\nInside corporate portal";
    cache.put(requested_url, mock_network_response);

    std::string second_buffer;
    bool second_check = cache.get(requested_url, second_buffer);
    
    ASSERT_TRUE(second_check);
    EXPECT_EQ(second_buffer, mock_network_response);
}

// Scenario 2: Multi-threaded simultaneous cache access stress test
TEST(ProxyIntegrationScenario, MultiThreadedStressAccess) {
    CacheManager& cache = CacheManager::getInstance();
    cache.clear();

    const int thread_count = 12;
    std::vector<std::thread> workers;

    for (int i = 0; i < thread_count; ++i) {
        workers.emplace_back([&cache, i]() {
            std::string personal_url = "http://load-balancer.local/node/" + std::to_string(i);
            std::string payload = "HTTP/1.1 200 OK\r\nContent-Length: 30\r\n\r\nCluster node payload metadata " + std::to_string(i);
            
            cache.put(personal_url, payload);
            
            std::string output;
            bool hit = cache.get(personal_url, output);
            
            EXPECT_TRUE(hit);
            EXPECT_EQ(output, payload);
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }
}

// Helper functions for Scenario 3
static void startMockServer(int port, std::atomic<bool>& running, std::atomic<int>& hitCount) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_GE(server_fd, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    ASSERT_GE(bind(server_fd, (struct sockaddr*)&address, sizeof(address)), 0);
    ASSERT_GE(listen(server_fd, 5), 0);

    while (running.load()) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(server_fd, &fds);
        struct timeval tv = {0, 100000}; // 100ms timeout
        int ret = select(server_fd + 1, &fds, nullptr, nullptr, &tv);
        if (ret <= 0) continue;

        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd >= 0) {
            hitCount++;
            char buf[1024];
            recv(client_fd, buf, sizeof(buf), 0); // read request
            std::string reply = "HTTP/1.1 200 OK\r\nContent-Length: 17\r\nCache-Control: public\r\nConnection: close\r\n\r\nMock Server Reply";
            send(client_fd, reply.data(), reply.size(), 0);
            close(client_fd);
        }
    }
    close(server_fd);
}

static std::string sendProxyRequest(int proxyPort, const std::string& hostPort, const std::string& path) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return "SOCKET_ERROR";

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(proxyPort);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return "CONNECT_ERROR";
    }

    std::string req = "GET http://" + hostPort + path + " HTTP/1.1\r\n"
                      "Host: " + hostPort + "\r\n"
                      "Connection: close\r\n\r\n";
    send(sock, req.data(), req.size(), 0);

    std::string resp;
    char buf[1024];
    while (true) {
        ssize_t bytes = recv(sock, buf, sizeof(buf), 0);
        if (bytes <= 0) break;
        resp.append(buf, bytes);
    }
    close(sock);
    return resp;
}

// Scenario 3: Full End-To-End Socket Proxy Integration Test
TEST(ProxyIntegrationScenario, EndToEndSocketProxyCaching) {
    const int mockPort = 19001;
    const int proxyPort = 19002;

    std::atomic<bool> mockRunning{true};
    std::atomic<int> mockHits{0};

    // 1. Start the Mock target HTTP server
    std::thread mockServerThread(startMockServer, mockPort, std::ref(mockRunning), std::ref(mockHits));
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // let server socket bind

    // 2. Configure and start our ProxyServer
    Config cfg;
    cfg.setPort(proxyPort);
    cfg.setThreadPoolSize(4);
    cfg.setCacheLimitMb(5);
    cfg.setPolicy("LRU");

    ProxyServer proxy(cfg);
    proxy.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // let proxy socket bind

    // Clear cache to isolate this test
    CacheManager::getInstance().clear();

    // 3. Fire first GET request to the proxy
    std::string res1 = sendProxyRequest(proxyPort, "127.0.0.1:19001", "/test-resource");
    EXPECT_NE(res1.find("Mock Server Reply"), std::string::npos);
    EXPECT_EQ(mockHits.load(), 1); // Mock server must be contacted (Cache Miss)

    // 4. Fire same GET request to the proxy again
    std::string res2 = sendProxyRequest(proxyPort, "127.0.0.1:19001", "/test-resource");
    EXPECT_NE(res2.find("Mock Server Reply"), std::string::npos);
    
    // Mock server hit count should STILL be 1 (Cache Hit!)
    EXPECT_EQ(mockHits.load(), 1);

    // 5. Clean up both servers
    proxy.stop();
    mockRunning = false;
    if (mockServerThread.joinable()) {
        mockServerThread.join();
    }
}
