include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Unit tests executable
add_executable(unit_tests
    testConfig.cpp
    testPolicy.cpp
    testCache.cpp
    testHttp.cpp
    testThreadPool.cpp
)

target_link_libraries(unit_tests PRIVATE proxy_core gtest_main)

# Scenario integration tests executable
add_executable(scenario_tests
    testScenario.cpp
)

target_link_libraries(scenario_tests PRIVATE proxy_core gtest_main)

add_test(NAME ProxyUnitTests COMMAND unit_tests)
add_test(NAME ProxyScenarioTests COMMAND scenario_tests)
