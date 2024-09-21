cmake_minimum_required(VERSION 3.16)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# Tests
function(add_test_executable name)
    add_executable(levelz-test-${name} "src/${name}.cpp" "src/test.h")
    target_include_directories(levelz-test-${name} PRIVATE "../include")
    add_test(NAME ${name} COMMAND levelz-test-${name})

    target_compile_options(levelz-test-${name} PRIVATE -coverage)
    target_link_options(levelz-test-${name} PRIVATE -coverage)
endfunction()

add_test_executable("coordinate")
add_test_executable("block")
add_test_executable("level")
add_test_executable("matrix")