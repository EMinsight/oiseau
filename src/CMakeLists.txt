file(
    GLOB_RECURSE
    OISEAU_CORE_SOURCES
    "oiseau/dg/*.cpp"
    "oiseau/io/*.cpp"
    "oiseau/mesh/*.cpp"
    "oiseau/plotting/*.cpp"
    "oiseau/utils/*.cpp"
)

set(OISEAU_PUBLIC_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)
set(OISEAU_CORE_SOURCES
    ${OISEAU_CORE_SOURCES}
    PARENT_SCOPE
)
