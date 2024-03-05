cmake_minimum_required(VERSION 3.16)

project(levelz-cpp CXX)
enable_testing()
set(CMAKE_CXX_STANDARD 17)

# Sources
add_library(levelz-cpp STATIC
    src/levelz.cpp
)
target_include_directories(levelz-cpp PUBLIC ${PROJECT_SOURCE_DIR}/include)