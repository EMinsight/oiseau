cmake_minimum_required(VERSION 3.18)

project(oiseau)

# building parameters
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# third party dependencies
add_subdirectory(vendor)
add_subdirectory(src)

# demos
add_subdirectory(demo)

# tests
enable_testing()
add_subdirectory(test)
