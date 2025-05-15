FetchContent_Declare(
    loguru
    GIT_REPOSITORY https://github.com/emilk/loguru
    GIT_TAG 4adaa185883e3c04da25913579c451d3c32cfac1
    GIT_SHALLOW 1
    GIT_PROGRESS 1
    FIND_PACKAGE_ARGS ""
)

if(NOT loguru_POPULATED)
    cmake_policy(SET CMP0169 OLD)
    FetchContent_Populate(loguru)
    add_library(loguru STATIC ${loguru_SOURCE_DIR}/loguru.cpp)
    target_include_directories(loguru PUBLIC ${loguru_SOURCE_DIR})
    target_compile_definitions(loguru PUBLIC LOGURU_WITH_STREAMS)
endif()
