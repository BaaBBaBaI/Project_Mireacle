cmake_minimum_required(VERSION 3.11)

project(HttpProxyServer 
        VERSION 1.0.0 
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(proxy_core STATIC
    src/cacheManager.cpp
)

target_include_directories(proxy_core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(proxy_core PRIVATE Threads::Threads)

add_executable(proxy_server src/main.cpp)
target_link_libraries(proxy_server PRIVATE proxy_core)

if(MSVC)
    target_compile_options(proxy_core PRIVATE /W4)
    target_compile_options(proxy_server PRIVATE /W4)
else()
    target_compile_options(proxy_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(proxy_server PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_subdirectory(tests)