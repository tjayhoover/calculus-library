cmake_minimum_required(VERSION 3.10.0)
project(calculus-library VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(calculus STATIC src/integration.cpp)
target_include_directories(calculus PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(bonds STATIC src/bond_pricing.cpp)
target_include_directories(bonds PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(bonds PRIVATE calculus)

add_library(options STATIC src/black_scholes.cpp)
target_include_directories(options PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(calculus-main main.cpp src/hw3.cpp)
target_link_libraries(calculus-main PRIVATE calculus bonds options)

include(CTest)
enable_testing()

add_subdirectory(tests)