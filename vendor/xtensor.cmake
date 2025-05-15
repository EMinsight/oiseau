FetchContent_Declare(
    xtl
    GIT_REPOSITORY https://github.com/xtensor-stack/xtl.git
    GIT_TAG 0.8.0
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS 0.8.0
)

FetchContent_Declare(
    xtensor
    GIT_REPOSITORY https://github.com/xtensor-stack/xtensor.git
    GIT_TAG 0.26.0
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS 0.26.0
)

FetchContent_Declare(
    xtensor-blas
    GIT_REPOSITORY https://github.com/xtensor-stack/xtensor-blas
    GIT_TAG 0.22.0
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS 0.22.0
)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

FetchContent_MakeAvailable(xtl xtensor xtensor-blas)

add_library(xtensor_stack INTERFACE)
target_link_libraries(
    xtensor_stack INTERFACE xtl xtensor xtensor-blas LAPACK::LAPACK BLAS::BLAS cblas
)
