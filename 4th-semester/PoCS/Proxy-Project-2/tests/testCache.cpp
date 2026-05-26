#include <gtest/gtest.h>
#include "cacheManager.h"
#include <string>

TEST(CacheManagerPutTest, PutStandardContent) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-put-1.com";
    std::string content = "<html><body>Standard Page</body></html>";
    EXPECT_NO_THROW(cache.put(url, content));
}

TEST(CacheManagerPutTest, PutEmptyContent) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-put-2.com";
    EXPECT_NO_THROW(cache.put(url, ""));
}

TEST(CacheManagerPutTest, PutLargeContent) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-put-3.com";
    std::string large_content(1024 * 1024, 'A');
    EXPECT_NO_THROW(cache.put(url, large_content));
}

TEST(CacheManagerPutTest, PutSpecialCharactersInUrl) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-put-4.com/search?q=query&mode=dark#header";
    std::string content = "Data";
    EXPECT_NO_THROW(cache.put(url, content));
}

TEST(CacheManagerPutTest, PutOverwriteExistingKey) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-put-5.com";
    cache.put(url, "Version 1");
    EXPECT_NO_THROW(cache.put(url, "Version 2"));
}

TEST(CacheManagerPutTest, PutEmptyUrlKey) {
    CacheManager& cache = CacheManager::getInstance();
    EXPECT_NO_THROW(cache.put("", "Empty Key Content"));
}

TEST(CacheManagerGetTest, GetCacheMiss) {
    CacheManager& cache = CacheManager::getInstance();
    std::string out_content;
    bool result = cache.get("http://never-existed-url.org", out_content);
    EXPECT_FALSE(result);
}

TEST(CacheManagerGetTest, GetCacheHitStandard) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-get-2.com";
    std::string expected_content = "Cached text data";
    cache.put(url, expected_content);
    std::string actual_content;
    bool result = cache.get(url, actual_content);
    ASSERT_TRUE(result);
    EXPECT_EQ(actual_content, expected_content);
}

TEST(CacheManagerGetTest, GetCacheHitUpdatedContent) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-get-3.com";
    cache.put(url, "Old Content");
    cache.put(url, "New Content");
    std::string actual_content;
    cache.get(url, actual_content);
    EXPECT_EQ(actual_content, "New Content");
}

TEST(CacheManagerGetTest, GetCacheHitEmptyContent) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-get-4.com";
    cache.put(url, "");
    std::string actual_content;
    bool result = cache.get(url, actual_content);
    ASSERT_TRUE(result);
    EXPECT_TRUE(actual_content.empty());
}

TEST(CacheManagerGetTest, GetEmptyUrlKey) {
    CacheManager& cache = CacheManager::getInstance();
    cache.put("", "Data for empty string");
    std::string actual_content;
    bool result = cache.get("", actual_content);
    ASSERT_TRUE(result);
    EXPECT_EQ(actual_content, "Data for empty string");
}

TEST(CacheManagerGetTest, GetLargeContentVerification) {
    CacheManager& cache = CacheManager::getInstance();
    std::string url = "http://test-get-6.com";
    std::string large_content(500000, 'B');
    cache.put(url, large_content);
    std::string actual_content;
    bool result = cache.get(url, actual_content);
    ASSERT_TRUE(result);
    EXPECT_EQ(actual_content.size(), 500000);
    EXPECT_EQ(actual_content, large_content);
}