include(GoogleTest)

add_executable(oiseau_test_mesh test_mesh.cpp)
target_link_libraries(oiseau_test_mesh gtest_main oiseau)
gtest_discover_tests(oiseau_test_mesh)
