FetchContent_Declare(
    loguru
    GIT_REPOSITORY https://github.com/emilk/loguru
    GIT_SHALLOW 1
    GIT_PROGRESS 1
)

if(NOT loguru_POPULATED)
    FetchContent_Populate(loguru)
    add_library(loguru INTERFACE)
    target_include_directories(loguru INTERFACE ${loguru_SOURCE_DIR})
    target_sources(loguru INTERFACE ${loguru_SOURCE_DIR}/loguru.cpp)
    target_compile_definitions(loguru INTERFACE LOGURU_WITH_STREAMS)
endif()
