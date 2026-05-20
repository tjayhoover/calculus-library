find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_integration test_integration.cpp)
target_link_libraries(test_integration PRIVATE GTest::gtest_main calculus)

gtest_discover_tests(test_integration)