FetchContent_Declare(
    blaze
    GIT_REPOSITORY https://bitbucket.org/blaze-lib/blaze.git
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS REQUIRED
)

FetchContent_MakeAvailable(blaze)
