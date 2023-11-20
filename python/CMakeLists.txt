cmake_minimum_required(VERSION 3.18)
project(oiseau_pybind11)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find_package(pybind11 REQUIRED)

add_subdirectory(.. oiseau)
pybind11_add_module(
    cpp MODULE oiseau/wrappers/oiseau.cpp oiseau/wrappers/mesh.cpp oiseau/wrappers/io.cpp
)
target_link_libraries(cpp PRIVATE oiseau)
target_include_directories(cpp PRIVATE ../src)
