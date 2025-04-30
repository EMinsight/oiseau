#pragma once

#include <concepts>
#include <ranges>
#include <xtensor/containers/xarray.hpp>

namespace oiseau::utils {

template <class Container>
concept FloatingArrayLike = std::ranges::contiguous_range<Container> &&
                            std::is_floating_point_v<typename Container::value_type>;

template <std::floating_point Real, FloatingArrayLike Container>
Container jacobi_p(unsigned n, Real alpha, Real beta, Container v);

template <std::floating_point Real, FloatingArrayLike Container>
Container grad_jacobi_p(int n, Real alpha, Real beta, Container v);

}  // namespace oiseau::utils
