#pragma once
#include <xtensor/core/xtensor_forward.hpp>

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefTetrahedron : public RefElement {
 public:
  explicit RefTetrahedron(unsigned order);
  xt::xarray<double> basis_function(const xt::xarray<double> &rst, int i, int j, int k) const;
  xt::xarray<double> grad_basis_function(const xt::xarray<double> &rst, int i, int j, int k) const;

 private:
  xt::xarray<double> vandermonde(const xt::xarray<double> &rst) const;
  xt::xarray<double> grad_vandermonde(const xt::xarray<double> &rst) const;
  xt::xarray<double> grad_operator(const xt::xarray<double> &v, const xt::xarray<double> &gv) const;
};

namespace detail {

xt::xarray<double> equilateral_xyz_to_rst(const xt::xarray<double> &coords);
xt::xarray<double> rst_to_abc(const xt::xarray<double> &rst);
xt::xarray<double> generate_tetrahedron_nodes(unsigned p);
xt::xarray<double> generate_tetrahedron_equidistant_nodes(unsigned n);
xt::xarray<double> warp_shift_face_3d(int p, double pval, const xt::xarray<double> &l2,
                                      const xt::xarray<double> &l3, const xt::xarray<double> &l4);
xt::xarray<double> eval_shift(int p, double pval, const xt::xarray<double> &l1,
                              const xt::xarray<double> &l2, const xt::xarray<double> &l3);
xt::xarray<double> eval_warp(int p, const xt::xarray<double> &xnodes,
                             const xt::xarray<double> &xout);

}  // namespace detail

}  // namespace oiseau::dg::nodal
