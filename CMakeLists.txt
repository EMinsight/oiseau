cmake_minimum_required(VERSION 3.24)

project(oiseau)

# building parameters
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "Debug"
        CACHE STRING
              "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
              FORCE
    )
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

option(OISEAU_BUILD_DEMO "Build demo" ON)
option(OISEAU_BUILD_TEST "Build test" ON)
option(OISEAU_BUILD_DOCS "Build Docs" OFF)
option(OISEAU_BUILD_BENC "Build Benc" OFF)

# third party dependencies
add_subdirectory(vendor)

# oiseau library
add_subdirectory(src)

# export oiseau target
add_library(oiseau SHARED)
target_link_libraries(oiseau PUBLIC oiseau_core)
target_link_libraries(oiseau PUBLIC oiseau_deps)
set_target_properties(oiseau PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# demos
if(OISEAU_BUILD_DEMO)
    add_subdirectory(demo)
endif()

# tests
if(OISEAU_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

# benchmarks
if(OISEAU_BUILD_BENC)
    add_subdirectory(benchmark)
endif()

if(OISEAU_BUILD_DOCS)
    add_subdirectory(doc)
endif()
