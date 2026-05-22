find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_integration integration/test_integration.cpp)
add_executable(test_simpsons integration/test_simpsons_method.cpp)
target_link_libraries(test_integration PRIVATE GTest::gtest_main calculus)
target_link_libraries(test_simpsons PRIVATE GTest::gtest_main calculus)
gtest_discover_tests(test_simpsons)
gtest_discover_tests(test_integration)