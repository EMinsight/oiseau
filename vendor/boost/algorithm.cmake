FetchContent_Declare(
    boost-algorithm
    GIT_REPOSITORY https://github.com/boostorg/algorithm
    GIT_SHALLOW 1
    GIT_PROGRESS 1
)

if(NOT boost-algorithm_POPULATED)
    FetchContent_Populate(boost-algorithm)
    add_library(boost_algorithm INTERFACE)
    add_library(Boost::algorithm ALIAS boost_algorithm)
    target_include_directories(boost_algorithm INTERFACE ${boost-algorithm_SOURCE_DIR}/include)
endif()
