#include <gtest/gtest.h>
#include "Config.h"
#include <fstream>

TEST(ConfigTest, DefaultValues) {
    Config cfg;
    EXPECT_EQ(cfg.getPort(), 8080);
    EXPECT_EQ(cfg.getThreadPoolSize(), 16);
    EXPECT_EQ(cfg.getCacheLimitMb(), 50);
    EXPECT_EQ(cfg.getPolicy(), "LRU");
}

TEST(ConfigTest, LoadMissingFileDefaults) {
    Config cfg;
    bool success = cfg.loadFromFile("missing_file_that_does_not_exist.txt");
    EXPECT_FALSE(success);
    EXPECT_EQ(cfg.getPort(), 8080);
    EXPECT_EQ(cfg.getThreadPoolSize(), 16);
}

TEST(ConfigTest, LoadValidConfig) {
    std::ofstream tmp("test_config.txt");
    tmp << "port=9090\n";
    tmp << "threads=4\n";
    tmp << "cache_limit_mb=100\n";
    tmp << "policy=FIFO\n";
    tmp.close();

    Config cfg("test_config.txt");
    EXPECT_EQ(cfg.getPort(), 9090);
    EXPECT_EQ(cfg.getThreadPoolSize(), 4);
    EXPECT_EQ(cfg.getCacheLimitMb(), 100);
    EXPECT_EQ(cfg.getPolicy(), "FIFO");

    std::remove("test_config.txt");
}

TEST(ConfigTest, ParseInvalidPort) {
    std::ofstream tmp("test_config_invalid.txt");
    tmp << "port=abc\n";
    tmp.close();

    Config cfg("test_config_invalid.txt");
    EXPECT_EQ(cfg.getPort(), 8080);

    std::remove("test_config_invalid.txt");
}

TEST(ConfigTest, ParseInvalidThreads) {
    std::ofstream tmp("test_config_invalid.txt");
    tmp << "threads=-5\n";
    tmp.close();

    Config cfg("test_config_invalid.txt");
    EXPECT_EQ(cfg.getThreadPoolSize(), 16);

    std::remove("test_config_invalid.txt");
}

TEST(ConfigTest, SettersAndGetters) {
    Config cfg;
    cfg.setPort(7070);
    cfg.setThreadPoolSize(32);
    cfg.setCacheLimitMb(250);
    cfg.setPolicy("FIFO");

    EXPECT_EQ(cfg.getPort(), 7070);
    EXPECT_EQ(cfg.getThreadPoolSize(), 32);
    EXPECT_EQ(cfg.getCacheLimitMb(), 250);
    EXPECT_EQ(cfg.getPolicy(), "FIFO");
}

TEST(ConfigTest, CommentHandling) {
    std::ofstream tmp("test_config_comments.txt");
    tmp << "# comment\n";
    tmp << "port=5000 # inline comment\n";
    tmp << "threads=8\n";
    tmp.close();

    Config cfg("test_config_comments.txt");
    EXPECT_EQ(cfg.getThreadPoolSize(), 8);

    std::remove("test_config_comments.txt");
}
