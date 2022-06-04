file(
    GLOB_RECURSE
    OISEAU_SOURCE_GLOB
    common/*.cpp
    assembly/*.cpp
    fem/*.cpp
    mesh/*.cpp
    plotting/*.cpp
)

set(OISEAU_SOURCES ${OISEAU_SOURCE_GLOB})
set(OISEAU_HEADER_DIR)

add_library(oiseau STATIC ${OISEAU_SOURCES})
target_include_directories(oiseau PUBLIC ${CMAKE_CURRENT_LIST_DIR})
