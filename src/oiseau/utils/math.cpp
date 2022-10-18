#include "oiseau/utils/math.hpp"
#include <array>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/jacobi.hpp>
#include <concepts>
#include <utility>
#include <vector>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xtensor.hpp>

namespace oiseau::utils {

template <std::floating_point Real, FloatingArrayLike Container>
Container jacobi_p(unsigned n, Real alpha, Real beta, Container v) {
  using boost::math::tgamma, boost::math::jacobi;
  Real norm = std::pow(2, alpha + beta + 1) / (2 * n + alpha + beta + 1);
  norm *= tgamma(n + alpha + 1) * tgamma(n + beta + 1);
  norm /= (tgamma(n + 1) * tgamma(n + alpha + beta + 1));
  auto partial = [n, alpha, beta, norm](auto &k) {
    k = jacobi(n, alpha, beta, k) / std::sqrt(norm);
  };
  std::for_each(v.begin(), v.end(), partial);
  return v;
}

template <std::floating_point Real, FloatingArrayLike Container>
Container grad_jacobi_p(int n, Real alpha, Real beta, Container v) {
  if (n == 0) {
    std::for_each(v.begin(), v.end(), [](auto &elm) { elm = 0; });
    return v;
  }
  double norm = std::sqrt(n * (n + alpha + beta + 1));
  auto output = jacobi_p(n - 1, alpha + 1, beta + 1, v);
  std::for_each(output.begin(), output.end(), [norm](auto &k) { k *= norm; });
  return output;
}

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
  return make_pair(std::move(x), std::move(w));
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

template std::vector<double> jacobi_p(unsigned n, double alpha, double beta, std::vector<double> v);
template std::vector<double> grad_jacobi_p(int n, double alpha, double beta, std::vector<double> v);

}  // namespace oiseau::utils
