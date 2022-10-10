cmake_minimum_required(VERSION 3.18)
project(oiseau_pybind11)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(pybind11 REQUIRED)

pybind11_add_module(cpp MODULE
    oiseau/wrappers/oiseau.cpp
    oiseau/wrappers/mesh.cpp
    oiseau/wrappers/io.cpp
)

add_subdirectory(.. oiseau)
target_link_libraries(cpp PUBLIC oiseau)
target_include_directories(cpp PUBLIC ../src)
