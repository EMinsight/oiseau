include(GoogleTest)

macro(add_test test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name} gtest_main oiseau)
    gtest_discover_tests(${test_name})
endmacro()

add_test(oiseau_test_mesh test_mesh.cpp)
add_test(oiseau_test_utils test_utils.cpp)
add_test(oiseau_test_io test_io.cpp)
