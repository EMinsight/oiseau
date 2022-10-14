cmake_minimum_required(VERSION 3.18)

project(oiseau)

# building parameters
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# third party dependencies
add_subdirectory(vendor)
add_subdirectory(src)

# export oiseau target
add_library(oiseau SHARED)
target_link_libraries(oiseau PUBLIC oiseau_core)
target_link_libraries(oiseau PUBLIC xtensor_stack Boost::math)

# demos
add_subdirectory(demo)

# tests
enable_testing()
add_subdirectory(test)
