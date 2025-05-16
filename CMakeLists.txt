cmake_minimum_required(VERSION 3.24)

project(oiseau LANGUAGES CXX)

# ------------------------------------------------------------------------------
# Build Configuration
# ------------------------------------------------------------------------------

# Enable compile commands for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require modern C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Debug build if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "Debug"
        CACHE STRING "Choose the type of build: Debug, Release, RelWithDebInfo, MinSizeRel." FORCE
    )
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ------------------------------------------------------------------------------
# Build Options
# ------------------------------------------------------------------------------

option(OISEAU_BUILD_DEMO "Build demo applications" ON)
option(OISEAU_BUILD_TEST "Build unit tests" ON)
option(OISEAU_BUILD_DOCS "Build documentation" OFF)
option(OISEAU_BUILD_BENC "Build benchmarks" OFF)
option(OISEAU_BUILD_COVR "Build with coverage" OFF)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

add_subdirectory(vendor)

# ------------------------------------------------------------------------------
# Library Target
# ------------------------------------------------------------------------------

add_subdirectory(src)

add_library(oiseau STATIC ${OISEAU_CORE_SOURCES})
set_target_properties(oiseau PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

target_include_directories(
    oiseau PUBLIC $<BUILD_INTERFACE:${OISEAU_PUBLIC_INCLUDE_DIR}> $<INSTALL_INTERFACE:include>
)

target_link_libraries(oiseau PUBLIC oiseau_deps)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ------------------------------------------------------------------------------
# Optional Subdirectories
# ------------------------------------------------------------------------------
if(OISEAU_BUILD_COVR)
    message(STATUS "Coverage build enabled")
    include(Coverage)
endif()

if(OISEAU_BUILD_DEMO)
    add_subdirectory(demo)
endif()

if(OISEAU_BUILD_TEST)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

if(OISEAU_BUILD_BENC)
    add_subdirectory(benchmark)
endif()

if(OISEAU_BUILD_DOCS)
    add_subdirectory(doc)
endif()

# ------------------------------------------------------------------------------
# Website
# ------------------------------------------------------------------------------
if(OISEAU_BUILD_DOCS AND OISEAU_BUILD_TEST)
    add_subdirectory(website)
endif()
