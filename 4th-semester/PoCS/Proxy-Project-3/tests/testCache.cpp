#include <gtest/gtest.h>
#include "CacheManager.h"
#include "LRUPolicy.h"
#include "FIFOPolicy.h"

TEST(CacheManagerTest, SingletonUniqueness) {
    CacheManager& cache1 = CacheManager::getInstance();
    CacheManager& cache2 = CacheManager::getInstance();
    EXPECT_EQ(&cache1, &cache2);
}

TEST(CacheManagerTest, CachePutGet) {
    CacheManager& cache = CacheManager::getInstance();
    cache.clear();
    
    std::string key = "http://example.com/test1";
    std::string content = "Hello World Caching";
    
    cache.put(key, content);
    
    std::string result;
    bool success = cache.get(key, result);
    EXPECT_TRUE(success);
    EXPECT_EQ(result, content);
}

TEST(CacheManagerTest, CacheMiss) {
    CacheManager& cache = CacheManager::getInstance();
    cache.clear();
    
    std::string result;
    bool success = cache.get("http://example.com/nonexistent", result);
    EXPECT_FALSE(success);
}

TEST(CacheManagerTest, CacheEvictionLRU) {
    CacheManager& cache = CacheManager::getInstance();
    // Configure with 1 MB limit (1024 * 1024 bytes)
    cache.configure(std::make_unique<LRUPolicy>(), 1); 
    
    // Create three chunks of ~400 KB each (total ~1.2 MB, exceeds 1 MB limit)
    std::string chunkA(400 * 1024, 'A');
    std::string chunkB(400 * 1024, 'B');
    std::string chunkC(400 * 1024, 'C');

    cache.put("A", chunkA);
    cache.put("B", chunkB);
    
    // Access A to make it recently used
    std::string tmp;
    cache.get("A", tmp);
    
    // Put C. This should evict B since A was touched and B is the least recently used.
    cache.put("C", chunkC);

    EXPECT_TRUE(cache.get("A", tmp));
    EXPECT_FALSE(cache.get("B", tmp));
    EXPECT_TRUE(cache.get("C", tmp));
}

TEST(CacheManagerTest, CacheEvictionFIFO) {
    CacheManager& cache = CacheManager::getInstance();
    // Configure with FIFO policy, 1 MB limit
    cache.configure(std::make_unique<FIFOPolicy>(), 1);

    std::string chunkA(400 * 1024, 'A');
    std::string chunkB(400 * 1024, 'B');
    std::string chunkC(400 * 1024, 'C');

    cache.put("A", chunkA);
    cache.put("B", chunkB);
    
    // Touch A. In FIFO, this shouldn't change eviction order
    std::string tmp;
    cache.get("A", tmp);

    // Put C. It should evict A (inserted first) despite A being touched.
    cache.put("C", chunkC);

    EXPECT_FALSE(cache.get("A", tmp));
    EXPECT_TRUE(cache.get("B", tmp));
    EXPECT_TRUE(cache.get("C", tmp));
}

TEST(CacheManagerTest, CacheClear) {
    CacheManager& cache = CacheManager::getInstance();
    cache.put("key", "value");
    EXPECT_GT(cache.getEntryCount(), 0);
    
    cache.clear();
    EXPECT_EQ(cache.getEntryCount(), 0);
    EXPECT_EQ(cache.getCurrentSize(), 0);
}

TEST(CacheManagerTest, ExceedsLimitOnFirstInsert) {
    CacheManager& cache = CacheManager::getInstance();
    cache.configure(std::make_unique<LRUPolicy>(), 1); // 1 MB limit
    
    // 2 MB chunk (larger than limit)
    std::string hugeChunk(2 * 1024 * 1024, 'X');
    cache.put("huge", hugeChunk);
    
    std::string tmp;
    // Should NOT be cached
    EXPECT_FALSE(cache.get("huge", tmp));
    EXPECT_EQ(cache.getEntryCount(), 0);
}
