macro(add_test test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name} PRIVATE gtest gtest_main oiseau)
    set_target_properties(
        ${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test
    )
    target_include_directories(${test_name} PUBLIC ${CMAKE_SOURCE_DIR}/test)
    gtest_discover_tests(${test_name})
endmacro()
