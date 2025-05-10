#include "oiseau/utils/math.hpp"

#include <cmath>
#include <vector>
#include <xtensor/containers/xtensor.hpp>

namespace oiseau::utils {

template <std::floating_point Real>
Real jacobi(unsigned n, Real alpha, Real beta, Real x) {
  if (n == 0) {
    return Real(1);
  }

  Real y0 = 1;
  Real y1 = (alpha + 1) + (alpha + beta + 2) * (x - 1) / Real(2);

  Real yk = y1;
  unsigned k = 2;
  Real k_max = n * (1 + std::numeric_limits<Real>::epsilon());

  while (k < k_max) {
    Real denom = 2 * k * (k + alpha + beta) * (2 * k + alpha + beta - 2);
    Real gamma1 =
        (2 * k + alpha + beta - 1) *
        ((2 * k + alpha + beta) * (2 * k + alpha + beta - 2) * x + alpha * alpha - beta * beta);
    Real gamma0 = -2 * (k + alpha - 1) * (k + beta - 1) * (2 * k + alpha + beta);
    yk = (gamma1 * y1 + gamma0 * y0) / denom;
    y0 = y1;
    y1 = yk;
    k += 1;
  }
  return yk;
}

template <std::floating_point Real, FloatingArrayLike Container>
Container jacobi_p(unsigned n, Real alpha, Real beta, Container v) {
  Real norm = std::pow(2, alpha + beta + 1) / (2 * n + alpha + beta + 1);
  norm *= std::tgamma(n + alpha + 1) * std::tgamma(n + beta + 1);
  norm /= (std::tgamma(n + 1) * std::tgamma(n + alpha + beta + 1));
  auto partial = [n, alpha, beta, norm](auto &k) {
    k = jacobi(n, alpha, beta, k) / std::sqrt(norm);
  };
  std::for_each(v.begin(), v.end(), partial);
  return v;
}

template <std::floating_point Real, FloatingArrayLike Container>
Container grad_jacobi_p(int n, Real alpha, Real beta, Container v) {
  if (n == 0) {
    std::fill(v.begin(), v.end(), 0);
    return v;
  }
  double norm = std::sqrt(n * (n + alpha + beta + 1));
  auto output = jacobi_p(n - 1, alpha + 1, beta + 1, v);
  std::for_each(output.begin(), output.end(), [norm](auto &k) { k *= norm; });
  return output;
}

template std::vector<double> jacobi_p(unsigned n, double alpha, double beta, std::vector<double> v);
template std::vector<double> grad_jacobi_p(int n, double alpha, double beta, std::vector<double> v);
template xt::xarray<double> jacobi_p(unsigned n, double alpha, double beta, xt::xarray<double> v);
template xt::xarray<double> grad_jacobi_p(int n, double alpha, double beta, xt::xarray<double> v);

}  // namespace oiseau::utils
