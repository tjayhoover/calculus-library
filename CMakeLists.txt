cmake_minimum_required(VERSION 3.10.0)
project(calculus-library VERSION 0.1.0 LANGUAGES C CXX)

add_library(calculus STATIC src/integration.cpp)
target_include_directories(calculus PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(bonds STATIC src/bond_pricing.cpp)
target_include_directories(bonds PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(bonds PRIVATE calculus)

add_executable(calculus-test main.cpp)
target_link_libraries(calculus-test PRIVATE calculus bonds)

include(CTest)
enable_testing()

add_subdirectory(tests)