FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS ""
)

FetchContent_MakeAvailable(Boost)
