set(MAKEINFO OFF)
set(ENABLE_PRIVATE_API ON)

FetchContent_Declare(
    gmsh
    GIT_REPOSITORY https://gitlab.onelab.info/gmsh/gmsh
    GIT_SHALLOW 1
    GIT_PROGRESS 1
)

FetchContent_MakeAvailable(gmsh)
