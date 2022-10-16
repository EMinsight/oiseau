include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(googletest.cmake)
include(xtensor.cmake)
include(boost/math.cmake)
include(boost/algorithm.cmake)

add_library(oiseau_deps INTERFACE)
target_link_libraries(oiseau_deps INTERFACE xtensor_stack Boost::math Boost::algorithm)
target_precompile_headers(
    oiseau_deps
    INTERFACE
    <boost/math/special_functions/gamma.hpp>
    <boost/math/special_functions/jacobi.hpp>
    <xtensor-blas/xlinalg.hpp>
    <xtensor/xarray.hpp>
    <xtensor/xio.hpp>
    <xtensor/xmath.hpp>
    <xtensor/xtensor.hpp>
)
