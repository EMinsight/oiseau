FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS ""
)

FetchContent_MakeAvailable(fmt)
