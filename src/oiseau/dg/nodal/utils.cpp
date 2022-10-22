#include "oiseau/dg/nodal/utils.hpp"
#include <boost/math/special_functions/gamma.hpp>
#include <cmath>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xview.hpp>
#include "oiseau/utils/math.hpp"

namespace oiseau::dg::nodal::utils {
std::pair<xt::xarray<double>, xt::xarray<double>> jacobi_gq(unsigned n, double alpha, double beta) {
  if (n == 0) {
    xt::xarray<double> x = {(alpha - beta) / (alpha + beta + 2)};
    xt::xarray<double> w = {2};
    return make_pair(std::move(w), std::move(x));
  }
  xt::xarray<double> h1 = 2 * xt::linspace<double>(0, n, n + 1) + alpha + beta;
  auto h1s = xt::view(h1, xt::range(0, n));
  auto lins = xt::arange<double>(1, n + 1);
  xt::xarray<double> m =
      xt::diag(-1.0 / 2.0 * (std::pow(alpha, 2) - std::pow(beta, 2)) / (h1 + 2) / h1) +
      xt::diag(2. / (h1s + 2) *
                   xt::sqrt(lins * (lins + alpha + beta) * (lins + alpha) * (lins + beta) /
                            (h1s + 1) / (h1s + 3)),
               1);
  if (alpha + beta == 0) m(0, 0) = 0;
  m += xt::transpose(m);
  auto [d, v] = xt::linalg::eigh(m);
  using boost::math::tgamma;
  double cte = std::pow(2, (alpha + beta + 1)) / (alpha + beta + 1) * tgamma(alpha + 1) *
               tgamma(beta + 1) / tgamma(alpha + beta + 1);
  xt::xarray<double> w = cte * xt::square(xt::view(v, 0, xt::all())), x = d;
  return {x, w};
}

xt::xarray<double> jacobi_gl(unsigned n, double alpha, double beta) {
  auto [x, _] = jacobi_gq(n - 2, alpha + 1.0, beta + 1.0);
  return xt::concatenate(xt::xtuple(-xt::ones<double>({1}), x, xt::ones<double>({1})));
}

xt::xarray<double> vandermonde_1d(unsigned n, const xt::xarray<double> &r) {
  std::array<size_t, 2> shape = {r.size(), n + 1};
  xt::xtensor<double, 2> output(shape);
  for (size_t i = 0; i < n + 1; ++i) {
    xt::view(output, xt::all(), i) = oiseau::utils::jacobi_p(i, 0.0, 0.0, r);
  }
  return output;
}

xt::xarray<double> grad_vandermonde_1d(unsigned n, const xt::xarray<double> &r) {
  std::array<size_t, 2> shape = {r.size(), n + 1};
  auto output = xt::xtensor<double, 2>::from_shape(shape);
  for (size_t i = 0; i < n + 1; ++i) {
    xt::view(output, xt::all(), i) = oiseau::utils::grad_jacobi_p(i, 0.0, 0.0, r);
  }
  return output;
}

xt::xarray<double> generate_triangle_equidistant_nodes(std::size_t n) {
  std::size_t n_p = (n + 1) * (n + 2) / 2;
  xt::xarray<double> l1 = xt::zeros<double>({n_p});
  xt::xarray<double> l3 = xt::zeros<double>({n_p});
  xt::xarray<double> out = xt::zeros<double>(xt::xarray<double>::shape_type{n_p, 3});

  std::size_t idx = 0;
  for (std::size_t i = 0; i < n + 1; ++i)
    for (std::size_t j = 0; j < n + 1 - i; ++j, ++idx) {
      l1[idx] = i * 1.0 / n;
      l3[idx] = j * 1.0 / n;
    }

#define l2 (1.0 - l1 - l3)
  xt::view(out, xt::all(), 0) = -l2 + l3;
  xt::view(out, xt::all(), 1) = (-l2 - l3 + 2.0 * l1) / std::sqrt(3.0);
#undef l2
  return out;
}

xt::xarray<double> warp_factor(std::size_t n, xt::xarray<double> &rout) {
  auto lgl_r = oiseau::dg::nodal::utils::jacobi_gl(n, 0.0, 0.0);
  auto r_eq = xt::linspace<double>(-1.0, 1.0, n + 1);
  auto v_eq = oiseau::dg::nodal::utils::vandermonde_1d(n, r_eq);
  xt::xarray<double> p_mat = xt::zeros<double>(xt::xarray<double>::shape_type{n + 1, rout.size()});
  for (std::size_t i = 0; i < n + 1; ++i)
    xt::view(p_mat, i, xt::all()) = oiseau::utils::jacobi_p(i, 0.0, 0.0, rout);
  auto l_mat = xt::linalg::solve(xt::transpose(v_eq), p_mat);
  std::cout << l_mat << std::endl;
  std::cout << p_mat << std::endl;
  auto warp = xt::linalg::dot(xt::transpose(l_mat), (-r_eq + lgl_r));
  auto zerof = xt::abs(rout) < 1.0 - 1e-10;
  auto sf = 1.0 - xt::pow((zerof * rout), 2);
  warp = warp / sf + warp * (zerof - 1);
  return warp;
}

}  // namespace oiseau::dg::nodal::utils
