macro(add_benchmark benchmark_name)
    add_executable(${benchmark_name} ${ARGN})
    target_link_libraries(${benchmark_name} oiseau)
    target_link_libraries(${benchmark_name} benchmark::benchmark benchmark::benchmark_main)
    gtest_discover_tests(${benchmark_name})
endmacro()

add_benchmark(oiseau_benchmark_oiseau benchmark_oiseau.cpp)
