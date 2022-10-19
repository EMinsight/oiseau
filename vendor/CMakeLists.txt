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
    <xtensor/xarray.hpp>
    <xtensor/xio.hpp>
    <xtensor/xmath.hpp>
    <xtensor/xtensor.hpp>
)

include(eigen.cmake)
include(blaze.cmake)

include(loguru.cmake)
target_link_libraries(oiseau_deps INTERFACE loguru)
target_precompile_headers(oiseau_deps INTERFACE <loguru.hpp>)

include(boost.cmake)
target_link_libraries(oiseau_deps INTERFACE Boost::boost)
target_precompile_headers(
    oiseau_deps INTERFACE <boost/math/special_functions/gamma.hpp>
    <boost/math/special_functions/jacobi.hpp>
)
