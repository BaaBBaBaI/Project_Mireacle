cmake_minimum_required(VERSION 3.10)


project(HttpProxyServer VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


add_executable(proxy_server)


target_include_directories(proxy_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_sources(proxy_server PRIVATE
    main.cpp
    cacheManager.cpp
    
)

target_link_libraries(proxy_server PRIVATE Threads::Threads)
