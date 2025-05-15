include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

if(OISEAU_BUILD_TEST)
    include(googletest.cmake)
endif()

if(OISEAU_BUILD_BENC)
    include(benchmark.cmake)
endif()

add_library(oiseau_deps INTERFACE)

include(xtensor.cmake)
target_link_libraries(oiseau_deps INTERFACE xtensor_stack)

include(fmt.cmake)
target_link_libraries(oiseau_deps INTERFACE fmt::fmt)

include(loguru.cmake)
target_link_libraries(oiseau_deps INTERFACE loguru)

# include(eigen.cmake)

# include(blaze.cmake)

# include(boost.cmake) target_link_libraries(oiseau_deps INTERFACE Boost::boost)

include(pybind11.cmake)
target_link_libraries(oiseau_deps INTERFACE pybind11::embed)
