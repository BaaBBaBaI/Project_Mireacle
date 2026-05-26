#include <gtest/gtest.h>
#include "cacheManager.h"
#include <thread>
#include <vector>
#include <string>

TEST(ProxyIntegrationScenario, ClassicCacheWorkflow) {
    CacheManager& cache = CacheManager::getInstance();
    std::string requested_url = "http://internal-corporate-portal.local/index.html";
    std::string buffer;

    bool first_check = cache.get(requested_url, buffer);
    ASSERT_FALSE(first_check);

    std::string mock_network_response = "HTTP/1.1 200 OK\r\nContent-Length: 23\r\n\r\nInside corporate portal";
    cache.put(requested_url, mock_network_response);

    std::string second_buffer;
    bool second_check = cache.get(requested_url, second_buffer);
    
    ASSERT_TRUE(second_check);
    EXPECT_EQ(second_buffer, mock_network_response);
}

TEST(ProxyIntegrationScenario, MultiThreadedStressAccess) {
    CacheManager& cache = CacheManager::getInstance();
    const int thread_count = 12;
    std::vector<std::thread> workers;

    for (int i = 0; i < thread_count; ++i) {
        workers.emplace_back([&cache, i]() {
            std::string personal_url = "http://load-balancer.local/node/" + std::to_string(i);
            std::string payload = "Cluster node payload metadata " + std::to_string(i);
            
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