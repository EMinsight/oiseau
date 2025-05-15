FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 171bd08ca987987c3c50f0fa5dd8914bdd42dd3b
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS ""
)

FetchContent_MakeAvailable(Eigen3)
