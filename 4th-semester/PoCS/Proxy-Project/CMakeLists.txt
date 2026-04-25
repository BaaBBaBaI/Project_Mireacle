cmake_minimum_required(VERSION 3.10)

project(HttpProxyServer 
        VERSION 1.0.0 
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(proxy_server 
    src/main.cpp 
    src/cacheManager.cpp
)

target_include_directories(proxy_server PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(proxy_server PRIVATE Threads::Threads)

if(MSVC)
    target_compile_options(proxy_server PRIVATE /W4)
else()
    target_compile_options(proxy_server PRIVATE -Wall -Wextra -Wpedantic)
endif()
