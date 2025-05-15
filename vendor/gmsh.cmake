set(MAKEINFO OFF)
set(ENABLE_PRIVATE_API ON)

find_package(GMSH)

FetchContent_Declare(
    gmsh
    GIT_REPOSITORY https://gitlab.onelab.info/gmsh/gmsh
    GIT_TAG gmsh_4_13_1
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS ""
)

FetchContent_MakeAvailable(gmsh)
