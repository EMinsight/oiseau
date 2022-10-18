FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    GIT_TAG origin/main
)

FetchContent_MakeAvailable(benchmark)
