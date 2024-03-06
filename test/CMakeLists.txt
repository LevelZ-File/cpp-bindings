cmake_minimum_required(VERSION 3.16)

include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Tests
function(add_test_executable name)
    add_executable(levelz-test-${name} "src/${name}.cpp" "src/test.h")
    target_link_libraries(levelz-test-${name} PRIVATE levelz-cpp)
    add_test(NAME ${name} COMMAND levelz-test-${name})
endfunction()

add_test_executable("coordinate")
add_test_executable("block")