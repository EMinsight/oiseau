#pragma once

#include <xtensor/xarray.hpp>

namespace oiseau::dg::nodal::utils {
std::pair<xt::xarray<double>, xt::xarray<double>> jacobi_gq(unsigned n, double alpha, double beta);
xt::xarray<double> jacobi_gl(unsigned n, double alpha, double beta);
xt::xarray<double> d_matrix_1d(const xt::xarray<double> &v, const xt::xarray<double> &gv);
xt::xarray<double> d_matrix_1d(unsigned n, const xt::xarray<double> &r);
xt::xarray<double> grad_vandermonde_1d(unsigned n, const xt::xarray<double> &r);
xt::xarray<double> vandermonde_1d(unsigned n, const xt::xarray<double> &r);
xt::xarray<double> d_matrix_2d(const xt::xarray<double> &v, const xt::xarray<double> &gv);
xt::xarray<double> grad_simplexp_2d(xt::xarray<double> ab, int i, int j);
xt::xarray<double> grad_vandermonde_2d(unsigned n, const xt::xarray<double> &rs);
xt::xarray<double> simplexp_2d(xt::xarray<double> ab, int i, int j);
xt::xarray<double> vandermonde_2d(unsigned n, const xt::xarray<double> &rs);
xt::xarray<double> generate_triangle_equidistant_nodes(std::size_t n);
xt::xarray<double> warp_factor(std::size_t n, xt::xarray<double> &rout);
xt::xarray<double> conversion_equilateral_xy_to_rs(const xt::xarray<double> &coords);
xt::xarray<double> conversion_rs_to_ab(const xt::xarray<double> &rs);
xt::xarray<double> generate_triangle_nodes(std::size_t n);
xt::xarray<double> generate_tetraedron_equidistant_nodes(std::size_t n);
xt::xarray<double> eval_warp(int p, const xt::xarray<double> &xnodes,
                             const xt::xarray<double> &xout);
xt::xarray<double> eval_shift(int p, double pval, const xt::xarray<double> &l1,
                              const xt::xarray<double> &l2, const xt::xarray<double> &l3);
xt::xarray<double> generate_tetrahedron_nodes(std::size_t n);
xt::xarray<double> warp_shift_face_3d(int p, double pval, double pval2,
                                      const xt::xarray<double> &l1, const xt::xarray<double> &l2,
                                      const xt::xarray<double> &l3, const xt::xarray<double> &l4);
xt::xarray<double> conversion_equilateral_xyz_to_rst(const xt::xarray<double> &coords);
xt::xarray<double> conversion_rst_to_abc(const xt::xarray<double> &rst);
xt::xarray<double> d_matrix_3d(const xt::xarray<double> &v, const xt::xarray<double> &gv);
xt::xarray<double> grad_simplexp_3d(xt::xarray<double> abc, int i, int j, int k);
xt::xarray<double> grad_vandermonde_3d(unsigned n, const xt::xarray<double> &rst);
xt::xarray<double> simplexp_3d(xt::xarray<double> abc, int i, int j, int k);
xt::xarray<double> vandermonde_3d(unsigned n, const xt::xarray<double> &rst);
}  // namespace oiseau::dg::nodal::utils
