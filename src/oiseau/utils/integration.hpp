#pragma once

#include <utility>
#include <xtensor/containers/xarray.hpp>

namespace oiseau::utils::integration {
std::pair<xt::xarray<double>, xt::xarray<double>> cubature(int order);
std::pair<xt::xarray<double>, xt::xarray<double>> quadrature(int order);
}  // namespace oiseau::utils::integration
