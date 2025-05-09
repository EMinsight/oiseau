file(
    GLOB_RECURSE
    OISEAU_CORE_SOURCES
    "oiseau/dg/*.cpp"
    "oiseau/io/*.cpp"
    "oiseau/mesh/*.cpp"
    "oiseau/plotting/*.cpp"
    "oiseau/utils/*.cpp"
)

set(OISEAU_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(oiseau_core STATIC ${OISEAU_CORE_SOURCES})

target_include_directories(
    oiseau_core PUBLIC $<BUILD_INTERFACE:${OISEAU_PUBLIC_INCLUDE_DIR}>
                       $<INSTALL_INTERFACE:include>${CMAKE_INSTALL_PREFIX}/include
)

target_precompile_headers(oiseau_core PUBLIC <iostream>)

if(TARGET oiseau_deps)
    target_link_libraries(oiseau_core PUBLIC oiseau_deps)
endif()
