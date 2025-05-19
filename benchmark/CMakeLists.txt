macro(add_benchmark benchmark_name)
    add_executable(${benchmark_name} ${ARGN})
    target_link_libraries(${benchmark_name} oiseau)
    target_link_libraries(${benchmark_name} benchmark::benchmark benchmark::benchmark_main)
    set_target_properties(
        ${benchmark_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/benchmarks
    )
endmacro()

add_benchmark(oiseau_benchmark_oiseau benchmark_oiseau.cpp)
add_benchmark(oiseau_benchmark_xtensor benchmark_xtensor.cpp)
