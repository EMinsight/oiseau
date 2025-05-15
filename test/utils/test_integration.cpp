#include <gtest/gtest.h>

#include <xtensor/views/xview.hpp>

#include "oiseau/utils/integration.hpp"

namespace {
double integral_xn(int n) {
  if (n % 2 == 1) {
    return 0.0;
  } else {
    return 2.0 / (n + 1);
  }
}
double integral_triangle_xn_ym(int n, int m) {
  double I1 = integral_xn(n) - integral_xn(n + 1);
  int mp1 = m + 1;
  double sign_term = std::pow(-1.0, mp1);
  double integral_term1 = 0.0;
  integral_term1 = sign_term * integral_xn(mp1);
  double integral_term2 = 2.0 * sign_term;
  double I2 = (integral_term1 - integral_term2) / mp1;
  return I1 + I2;
}

}  // namespace

TEST(test_integration, test_gauss_quadrature) {
  // test quadrature for x^m  for m= 0, ..., 2*n - 1
  for (int n = 1; n < 50; ++n) {
    auto [nodes, weights] = oiseau::utils::integration::quadrature(n);
    for (int m = 0; m < n; ++m) {  // TODO(tiagovla): check why not m<=n
      double res = integral_xn(m);
      auto sum = xt::sum(xt::pow(nodes, m) * weights)();
      EXPECT_NEAR(res, sum, 1e-14) << "Failed for n = " << n << ", m = " << m;
    }
  }
}

TEST(test_integration, test_cubature) {
  // test cubature for x^i + y^j
  for (int n = 1; n <= 40; ++n) {
    auto [nodes, weights] = oiseau::utils::integration::cubature(n);
    auto x = xt::col(nodes, 0);
    auto y = xt::col(nodes, 1);
    for (int i = 0; i < n; ++i) {    // TODO(tiagovla): check why not i<=n
      for (int j = 0; j < n; ++j) {  // TODO(tiagovla): check why not j<=n
        double res = integral_triangle_xn_ym(i, j);
        auto z = xt::pow(x, i) + xt::pow(y, j);
        auto sum = xt::sum(z * weights)();
        EXPECT_NEAR(res, sum, 5e-14)
            << "Failed for order " << n << " with i = " << i << ", j = " << j;
      }
    }
  }
}
