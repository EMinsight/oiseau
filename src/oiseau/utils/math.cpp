#include "oiseau/utils/math.hpp"
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/jacobi.hpp>
#include <utility>
#include <vector>
#include <xtensor/containers/xtensor.hpp>

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
