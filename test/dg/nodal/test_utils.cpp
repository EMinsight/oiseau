#include <gtest/gtest.h>
#include "oiseau/dg/nodal/utils.hpp"

#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh)                       \
  EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";           \
  for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) { \
    EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;     \
  }
using namespace oiseau::dg::nodal::utils;
TEST(test_dg_nodal_utils, test_jacobi_gq) {
  unsigned n = 3;
  double alpha = 1.0, beta = 2.0;
  auto [x, w] = jacobi_gq(n, alpha, beta);
  xt::xarray<double> x_expected = {-0.65077886, -0.15637043, 0.37348938, 0.79729627};
  xt::xarray<double> w_expected = {0.08666291, 0.44123335, 0.59015336, 0.21528371};
  EXPECT_FLOATS_NEARLY_EQ(x, x_expected, 0.0001);
  EXPECT_FLOATS_NEARLY_EQ(w, w_expected, 0.0001);
}

TEST(test_dg_nodal_utils, test_jacobi_gl) {
  unsigned n = 4;
  double alpha = 1.0, beta = 2.0;
  auto output = jacobi_gl(n, alpha, beta);
  xt::xarray<double> expected = {-1., -0.4611587, 0.10438533, 0.62950065, 1.};
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.0001);
}

TEST(test_dg_nodal_utils, test_vandermonde_1d) {
  unsigned n = 4;
  xt::xarray<double> r = {0.1, 0.3, 0.7, 0.9};
  auto output = vandermonde_1d(n, r);
  xt::xarray<double> expected = {{0.70710678, 0.12247449, -0.76685233, -0.27594723, 0.71687369},
                                 {0.70710678, 0.36742346, -0.57711567, -0.71559198, 0.1547238},
                                 {0.70710678, 0.85732141, 0.37156763, -0.36013452, -0.87411656},
                                 {0.70710678, 1.10227038, 1.13051426, 0.88396656, 0.44110205}};
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.0001);
}

TEST(test_dg_nodal_utils, test_grad_vandermonde_1d) {
  unsigned n = 4;
  xt::xarray<double> r = {0.1, 0.3, 0.7, 0.9};
  auto output = grad_vandermonde_1d(n, r);
  xt::xarray<double> expected = {{0., 1.22474487, 0.47434165, -2.66593089, -1.55386715},
                                 {0., 1.22474487, 1.42302495, -1.54343367, -3.77064691},
                                 {0., 1.22474487, 3.32039154, 4.06905241, 1.59629356},
                                 {0., 1.22474487, 4.26907484, 8.55904127, 12.74383196}};

  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.0001);
}
