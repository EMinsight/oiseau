#include "oiseau/dg/nodal/utils.hpp"
#include <boost/math/special_functions/gamma.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xtensor.hpp>
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
}  // namespace oiseau::dg::nodal::utils
