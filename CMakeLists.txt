cmake_minimum_required(VERSION 3.16)

project(levelz-cpp 
    LANGUAGES C CXX 
    VERSION 0.1.0 
    DESCRIPTION "C/C++ implementation of the LevelZ File Format"
    HOMEPAGE_URL "https://github.com/LevelZ-File/cpp-bindings"
)
set(CMAKE_CXX_STANDARD 17)

# Sources
add_library(levelz-cpp INTERFACE)
target_include_directories(levelz-cpp INTERFACE include)

# Testing
enable_testing()
add_subdirectory(test)

# Documentation
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/build/Doxyfile.in)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()
