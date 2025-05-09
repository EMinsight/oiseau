include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

if(OISEAU_BUILD_TEST)
    include(googletest.cmake)
endif()
if(OISEAU_BUILD_BENCH)
    include(benchmark.cmake)
endif()

add_library(oiseau_deps INTERFACE)

include(xtensor.cmake)
target_link_libraries(oiseau_deps INTERFACE xtensor_stack)
target_precompile_headers(
    oiseau_deps
    INTERFACE
    <xtensor-blas/xlinalg.hpp>
    <xtensor/containers/xarray.hpp>
    <xtensor/io/xio.hpp>
    <xtensor/core/xmath.hpp>
    <xtensor/containers/xtensor.hpp>
    <xtensor/views/xview.hpp>
    <xtensor/containers/xadapt.hpp>
)

include(fmt.cmake)
target_link_libraries(oiseau_deps INTERFACE fmt::fmt)
target_precompile_headers(oiseau_deps INTERFACE <fmt/ranges.h> <fmt/core.h>)

include(eigen.cmake)
# include(blaze.cmake)

include(loguru.cmake)
target_link_libraries(oiseau_deps INTERFACE loguru)

include(boost.cmake)
target_link_libraries(oiseau_deps INTERFACE Boost::boost)
target_precompile_headers(
    oiseau_deps INTERFACE <boost/math/special_functions/gamma.hpp>
    <boost/math/special_functions/jacobi.hpp>
)

target_precompile_headers(
    oiseau_deps
    INTERFACE
    <string>
    <vector>
    <array>
    <cmath>
    <iostream>
)

include(pybind11.cmake)
target_link_libraries(oiseau_deps INTERFACE pybind11::embed)

target_precompile_headers(
    oiseau_deps INTERFACE <pybind11/embed.h> <pybind11/numpy.h> <pybind11/pytypes.h>
    <pybind11/stl.h>
)
