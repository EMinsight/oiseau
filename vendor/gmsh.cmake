set(MAKEINFO OFF)
set(ENABLE_PRIVATE_API ON)

find_package(GMSH)

FetchContent_Declare(
    gmsh
    GIT_REPOSITORY https://gitlab.onelab.info/gmsh/gmsh
    GIT_TAG ${GMSH_VERSION}
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS $GMSH_VERSION
)

FetchContent_MakeAvailable(gmsh)
