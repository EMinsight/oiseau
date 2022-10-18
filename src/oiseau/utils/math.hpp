#pragma once

#include <concepts>
#include <ranges>
#include <xtensor/xarray.hpp>

namespace oiseau::utils {

template <class Container>
concept FloatingArrayLike = std::ranges::contiguous_range<Container> &&
    std::is_floating_point_v<typename Container::value_type>;

template <std::floating_point Real, FloatingArrayLike Container>
Container jacobi_p(unsigned n, Real alpha, Real beta, Container v);

template <std::floating_point Real, FloatingArrayLike Container>
Container grad_jacobi_p(int n, Real alpha, Real beta, Container v);

std::pair<xt::xarray<double>, xt::xarray<double>> jacobi_gq(unsigned n, double alpha, double beta);
xt::xarray<double> jacobi_gl(unsigned n, double alpha, double beta);
xt::xarray<double> vandermonde_1d(unsigned n, const xt::xarray<double> &r);
xt::xarray<double> grad_vandermonde_1d(unsigned n, const xt::xarray<double> &r);

}  // namespace oiseau::utils
