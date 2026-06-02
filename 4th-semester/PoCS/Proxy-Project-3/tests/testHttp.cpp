#include <gtest/gtest.h>
#include "HttpRequest.h"
#include "HttpResponse.h"

// ================= HTTP REQUEST TESTS =================

TEST(HttpParserTest, Request_ValidGet) {
    std::string raw = "GET /index.html HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "User-Agent: test\r\n\r\n";
    HttpRequest req;
    EXPECT_TRUE(req.parse(raw));
    EXPECT_EQ(req.getMethod(), "GET");
    EXPECT_EQ(req.getUrl(), "/index.html");
    EXPECT_EQ(req.getHost(), "example.com");
    EXPECT_EQ(req.getPort(), 80);
    EXPECT_EQ(req.getHeader("User-Agent"), "test");
}

TEST(HttpParserTest, Request_ValidConnect) {
    std::string raw = "CONNECT google.com:443 HTTP/1.1\r\n"
                      "Host: google.com:443\r\n\r\n";
    HttpRequest req;
    EXPECT_TRUE(req.parse(raw));
    EXPECT_EQ(req.getMethod(), "CONNECT");
    EXPECT_EQ(req.getUrl(), "google.com:443");
    EXPECT_EQ(req.getHost(), "google.com");
    EXPECT_EQ(req.getPort(), 443);
}

TEST(HttpParserTest, Request_AbsoluteUrlGet) {
    std::string raw = "GET http://example.org:8080/path/file.txt HTTP/1.1\r\n"
                      "Host: example.org:8080\r\n\r\n";
    HttpRequest req;
    EXPECT_TRUE(req.parse(raw));
    EXPECT_EQ(req.getMethod(), "GET");
    EXPECT_EQ(req.getUrl(), "http://example.org:8080/path/file.txt");
    EXPECT_EQ(req.getHost(), "example.org");
    EXPECT_EQ(req.getPort(), 8080);
}

TEST(HttpParserTest, Request_Invalid) {
    std::string raw = "BAD REQUEST STREAM";
    HttpRequest req;
    EXPECT_FALSE(req.parse(raw));
    EXPECT_FALSE(req.valid());
}

TEST(HttpParserTest, Request_HeaderCaseInsensitive) {
    std::string raw = "GET / HTTP/1.1\r\n"
                      "Host: localhost\r\n"
                      "X-TEST-HEADER: Value123\r\n\r\n";
    HttpRequest req;
    EXPECT_TRUE(req.parse(raw));
    EXPECT_EQ(req.getHeader("x-test-header"), "Value123");
    EXPECT_EQ(req.getHeader("X-TEST-HEADER"), "Value123");
    EXPECT_EQ(req.getHeader("X-Test-Header"), "Value123");
}

TEST(HttpParserTest, Request_ToRawString) {
    std::string raw = "GET http://example.com/api HTTP/1.1\r\n"
                      "Host: example.com\r\n"
                      "Connection: keep-alive\r\n\r\n";
    HttpRequest req;
    ASSERT_TRUE(req.parse(raw));
    std::string formatted = req.toRawString();
    
    // Path should be relative /api instead of http://example.com/api
    EXPECT_NE(formatted.find("GET /api HTTP/1.1"), std::string::npos);
    // Connection must be forced to close
    EXPECT_NE(formatted.find("connection: close"), std::string::npos);
    EXPECT_EQ(formatted.find("keep-alive"), std::string::npos);
}

// ================= HTTP RESPONSE TESTS =================

TEST(HttpParserTest, Response_Valid) {
    std::string raw = "HTTP/1.1 200 OK\r\n"
                      "Content-Length: 12\r\n"
                      "Content-Type: text/plain\r\n\r\n"
                      "Hello Server";
    HttpResponse res;
    EXPECT_TRUE(res.parse(raw));
    EXPECT_EQ(res.getVersion(), "HTTP/1.1");
    EXPECT_EQ(res.getStatusCode(), 200);
    EXPECT_EQ(res.getStatusMessage(), "OK");
    EXPECT_EQ(res.getHeader("Content-Length"), "12");
    EXPECT_EQ(res.getBody(), "Hello Server");
}

TEST(HttpParserTest, Response_Invalid) {
    std::string raw = "NOT AN HTTP RESPONSE";
    HttpResponse res;
    EXPECT_FALSE(res.parse(raw));
}

TEST(HttpParserTest, Response_IsCacheableStandard) {
    std::string raw = "HTTP/1.1 200 OK\r\n"
                      "Content-Length: 10\r\n\r\n"
                      "1234567890";
    HttpResponse res;
    ASSERT_TRUE(res.parse(raw));
    EXPECT_TRUE(res.isCacheable());
}

TEST(HttpParserTest, Response_IsCacheableNon200) {
    std::string raw = "HTTP/1.1 404 Not Found\r\n\r\n";
    HttpResponse res;
    ASSERT_TRUE(res.parse(raw));
    EXPECT_FALSE(res.isCacheable());
}

TEST(HttpParserTest, Response_IsCacheableNoStore) {
    std::string raw = "HTTP/1.1 200 OK\r\n"
                      "Cache-Control: private, no-store, must-revalidate\r\n\r\n"
                      "data";
    HttpResponse res;
    ASSERT_TRUE(res.parse(raw));
    EXPECT_FALSE(res.isCacheable());
}

TEST(HttpParserTest, Response_IsCacheablePragma) {
    std::string raw = "HTTP/1.1 200 OK\r\n"
                      "Pragma: no-cache\r\n\r\n"
                      "data";
    HttpResponse res;
    ASSERT_TRUE(res.parse(raw));
    EXPECT_FALSE(res.isCacheable());
}
