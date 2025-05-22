// Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
//
// This file is part of oiseau (https://github.com/tiagovla/oiseau)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <xtensor/core/xtensor_forward.hpp>

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefHexahedron : public RefElement {
 public:
  explicit RefHexahedron(unsigned order);
  xt::xarray<double> basis_function(const xt::xarray<double>& rst, int i, int j, int k) const;
  xt::xarray<double> grad_basis_function(const xt::xarray<double>& rst, int i, int j, int k) const;

 private:
  xt::xarray<double> vandermonde(const xt::xarray<double>& rst) const;
  xt::xarray<double> grad_vandermonde(const xt::xarray<double>& rst) const;
  xt::xarray<double> grad_operator(const xt::xarray<double>& v, const xt::xarray<double>& gv) const;
};

namespace detail {

xt::xarray<double> generate_hexahedron_nodes(unsigned order);

}
}  // namespace oiseau::dg::nodal
