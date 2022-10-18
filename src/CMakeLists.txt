file(
    GLOB_RECURSE
    OISEAU_SOURCE_GLOB
    oiseau/dg/*.cpp
    oiseau/io/*.cpp
    oiseau/mesh/*.cpp
    oiseau/plotting/*.cpp
    oiseau/utils/*.cpp
)

set(OISEAU_SOURCES ${OISEAU_SOURCE_GLOB})
set(OISEAU_HEADERS ${CMAKE_CURRENT_LIST_DIR})

add_library(oiseau_core INTERFACE)
target_sources(oiseau_core INTERFACE ${OISEAU_SOURCES})
target_include_directories(oiseau_core INTERFACE ${OISEAU_HEADERS})
target_precompile_headers(oiseau_core INTERFACE <iostream>)
