#include <xtensor/xarray.hpp>

namespace oiseau::dg::nodal::utils {
std::pair<xt::xarray<double>, xt::xarray<double>> jacobi_gq(unsigned n, double alpha, double beta);
xt::xarray<double> jacobi_gl(unsigned n, double alpha, double beta);
xt::xarray<double> vandermonde_1d(unsigned n, const xt::xarray<double> &r);
xt::xarray<double> grad_vandermonde_1d(unsigned n, const xt::xarray<double> &r);
xt::xarray<double> generate_triangle_equidistant_nodes(std::size_t n);
xt::xarray<double> warp_factor(std::size_t n, xt::xarray<double> &rout);
}  // namespace oiseau::dg::nodal::utils
