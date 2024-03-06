cmake_minimum_required(VERSION 3.16)

include(CTest)

# Tests
function(add_test_executable name)
    add_executable(levelz-test-${name} "src/${name}.cpp" "src/test.h")
    target_link_libraries(levelz-test-${name} PRIVATE levelz-cpp)
    add_test(NAME ${name} COMMAND levelz-test-${name})
endfunction()

add_test_executable("coordinate")