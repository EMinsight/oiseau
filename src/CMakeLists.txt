file(
    GLOB_RECURSE
    OISEAU_SOURCE_GLOB
    oiseau/common/*.cpp
    oiseau/assembly/*.cpp
    oiseau/dg/*.cpp
    oiseau/mesh/*.cpp
    oiseau/plotting/*.cpp
)

set(OISEAU_SOURCES ${OISEAU_SOURCE_GLOB})

add_library(oiseau STATIC ${OISEAU_SOURCES})
target_include_directories(oiseau PUBLIC ${CMAKE_CURRENT_LIST_DIR})
