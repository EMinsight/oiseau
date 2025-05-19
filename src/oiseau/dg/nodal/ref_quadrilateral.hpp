#pragma once
#include <xtensor/core/xtensor_forward.hpp>

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefQuadrilateral : public RefElement {
 public:
  explicit RefQuadrilateral(unsigned order);
  static xt::xarray<double> basis_function(const xt::xarray<double> &rs, int i, int j);
  static xt::xarray<double> grad_basis_function(const xt::xarray<double> &rs, int i, int j);

 private:
  xt::xarray<double> vandermonde(const xt::xarray<double> &rs) const;
  xt::xarray<double> grad_vandermonde(const xt::xarray<double> &rs) const;
  xt::xarray<double> grad_operator(const xt::xarray<double> &v, const xt::xarray<double> &gv) const;
};

namespace detail {

xt::xarray<double> generate_quadrilateral_nodes(unsigned order);

}  // namespace detail
}  // namespace oiseau::dg::nodal
