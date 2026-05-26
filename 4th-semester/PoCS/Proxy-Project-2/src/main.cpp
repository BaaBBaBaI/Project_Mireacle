#include "cacheManager.h"
#include <iostream>


int main() {
    std::cout << "Starting Corporate HTTP Proxy Server..." << std::endl;

    
    CacheManager& cache = CacheManager::getInstance();
    
    std::string response;
    
 
    cache.get("http://example.com", response);
    cache.put("http://example.com", "<html><body>Example</body></html>");
    cache.get("http://example.com", response);

    std::cout << "Proxy Server shutdown." << std::endl;
    return 0;
}