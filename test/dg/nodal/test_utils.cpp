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

TEST(test_dg_nodal_utils, test_generate_triangle_equidistant_nodes) {
  xt::xarray<double> output = generate_triangle_equidistant_nodes(2);
  xt::xarray<double> expected = {{-1., 0., 1., -0.5, 0.5, 0.},
                                 {-0.577, -0.577, -0.577, 0.289, 0.289, 1.155},
                                 {0., 0., 0., 0., 0., 0.}};
  expected = xt::transpose(expected);
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_warp_factor) {
  xt::xarray<double> r = {0.1, 0.5, 0.9};
  xt::xarray<double> output = warp_factor(3, r);
  xt::xarray<double> expected = {0.038, 0.192, 0.346};
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_simplexp_2d) {
  xt::xarray<double> ab = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
  ab = xt::transpose(ab);
  xt::xarray<double> output = simplexp_2d(ab, 1, 2);
  xt::xarray<double> expected{0, -74.097064, -448.25662, -1502.7619, -3772.2142};
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_grad_simplexp_2d) {
  unsigned order = 3;
  auto rs = conversion_equilateral_xy_to_rs(generate_triangle_nodes(order));
  auto ab = conversion_rs_to_ab(rs);
  xt::xarray<double> output = grad_simplexp_2d(ab, 1, 1);
  xt::xarray<double> expected = {
      {-2.1213, -2.1213, -2.1213, -2.1213, 0.8103, 1.4142, 0.8103, 5.5537, 5.5537, 8.4853},
      {-6.3640, -3.4324, 1.3110, 4.2426, -3.4324, 0.7071, 4.2426, 1.3110, 4.2426, 4.2426}};
  expected = xt::transpose(expected);
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_generate_triangle_nodes) {
  unsigned order = 3;
  auto output = generate_triangle_nodes(order);
  xt::xarray<double> expected = {
      {-1.0000, -0.4472, 0.4472, 1.0000, -0.7236, -0.0000, 0.7236, -0.2764, 0.2764, 0},
      {-0.5774, -0.5774, -0.5774, -0.5774, -0.0986, -0.0000, -0.0986, 0.6760, 0.6760, 1.1547}};
  expected = xt::transpose(expected);
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_conversion_equilateral_xy_to_rs) {
  xt::xarray<double> xy = {{1, 2, 3}, {2, 3, 4}};
  xy = xt::transpose(xy);
  auto output = conversion_equilateral_xy_to_rs(xy);
  xt::xarray<double> expected = {{-0.4880, 1.9761}, {-0.0654, 3.1308}, {0.3573, 4.2855}};
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_conversion_rs_to_ab) {
  xt::xarray<double> rs = {
      {-1.0000, -0.4472, 0.4472, 1.0000, -1.0000, -0.3333, 0.4472, -1.0000, -0.4472, -1.0000},
      {-1.0000, -1.0000, -1.0000, -1.0000, -0.4472, -0.3333, -0.4472, 0.4472, 0.4472, 1.0000}};
  rs = xt::transpose(rs);
  auto output = conversion_rs_to_ab(rs);
  xt::xarray<double> expected = {
      {-1.0000, -0.4472, 0.4472, 1.0000, -1.0000, -0.0000, 1.0000, -1.0000, 1.0000, -1.0000},
      {-1.0000, -1.0000, -1.0000, -1.0000, -0.4472, -0.3333, -0.4472, 0.4472, 0.4472, 1.0000}};
  expected = xt::transpose(expected);
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_vandermonde_2d) {
  unsigned order = 3;
  auto rs = conversion_equilateral_xy_to_rs(generate_triangle_nodes(order));
  auto output = vandermonde_2d(order, rs);
  xt::xarray<double> expected = {
      {0.7071, -1.0000, 1.2247, -1.4142, -1.7321, 2.1213, -2.4495, 2.7386, -3.1623, -3.7417},
      {0.7071, -1.0000, 1.2247, -1.4142, -0.7746, 0.9487, -1.0954, -0.5477, 0.6325, 1.6733},
      {0.7071, -1.0000, 1.2247, -1.4142, 0.7746, -0.9487, 1.0954, -0.5477, 0.6325, -1.6733},
      {0.7071, -1.0000, 1.2247, -1.4142, 1.7321, -2.1213, 2.4495, 2.7386, -3.1623, 3.7417},
      {0.7071, -0.1708, -0.5477, 0.6325, -1.2533, -0.5863, 1.2628, 1.4340, 1.5478, -1.4177},
      {0.7071, -0.0000, -0.6804, 0.4190, -0.0000, -0.0000, 0.0000, -0.6086, -0.9370, 0.0000},
      {0.7071, -0.1708, -0.5477, 0.6325, 1.2533, 0.5863, -1.2628, 1.4340, 1.5478, 1.4177},
      {0.7071, 1.1708, 0.5477, -0.6325, -0.4787, -1.5350, -2.2426, 0.2092, 0.9821, -0.0790},
      {0.7071, 1.1708, 0.5477, -0.6325, 0.4787, 1.5350, 2.2426, 0.2092, 0.9821, 0.0790},
      {0.7071, 2.0000, 3.6742, 5.6569, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
  };
  EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.01);
}

TEST(test_dg_nodal_utils, test_grad_vandermonde_2d) {
  unsigned order = 3;
  auto rs = conversion_equilateral_xy_to_rs(generate_triangle_nodes(order));
  auto output = grad_vandermonde_2d(order, rs);
  xt::xarray<double> expected_r = {
      {0, 0, 0, 0, 1.7321, -2.1213, 2.4495, -8.2158, 9.4868, 22.4499},
      {0, 0, 0, 0, 1.7321, -2.1213, 2.4495, -3.6742, 4.2426, 0.0000},
      {0, 0, 0, 0, 1.7321, -2.1213, 2.4495, 3.6742, -4.2426, -0.0000},
      {0, 0, 0, 0, 1.7321, -2.1213, 2.4495, 8.2158, -9.4868, 22.4499},
      {0, 0, 0, 0, 1.7321, 0.8103, -1.7452, -5.9450, -6.4168, 11.7549},
      {0, 0, 0, 0, 1.7321, 1.4142, -1.6330, -0.0000, -0.0000, -2.4944},
      {0, 0, 0, 0, 1.7321, 0.8103, -1.7452, 5.9450, 6.4168, 11.7549},
      {0, 0, 0, 0, 1.7321, 5.5537, 8.1138, -2.2708, -10.6595, 1.7150},
      {0, 0, 0, 0, 1.7321, 5.5537, 8.1138, 2.2708, 10.6595, 1.7150},
      {0, 0, 0, 0, 1.7321, 8.4853, 24.4949, 0, 0, 0},
  };
  xt::xarray<double> expected_s = {
      {0, 1.5000, -4.8990, 10.6066, 0.8660, -6.3640, 15.9217, -2.7386, 14.2302, 5.6125},
      {0, 1.5000, -4.8990, 10.6066, 0.8660, -3.4324, 7.7974, -0.4678, -1.6734, -2.5100},
      {0, 1.5000, -4.8990, 10.6066, 0.8660, 1.3110, -5.3479, 3.2064, -5.9161, 2.5100},
      {0, 1.5000, -4.8990, 10.6066, 0.8660, 4.2426, -13.4722, 5.4772, 4.7434, 16.8375},
      {0, 1.5000, -1.5139, -1.3110, 0.8660, -3.4324, -0.5256, -1.9817, 3.6563, 2.9387},
      {0, 1.5000, -0.8165, -2.3570, 0.8660, 0.7071, -0.8165, 0.9129, -1.0541, -1.2472},
      {0, 1.5000, -1.5139, -1.3110, 0.8660, 4.2426, -1.2195, 3.9634, 10.0732, 8.8162},
      {0, 1.5000, 3.9634, 3.4324, 0.8660, 1.3110, -2.1688, -0.7569, -2.7076, 0.4288},
      {0, 1.5000, 3.9634, 3.4324, 0.8660, 4.2426, 10.2826, 1.5139, 7.9518, 1.2863},
      {0, 1.5000, 7.3485, 21.2132, 0.8660, 4.2426, 12.2474, 0, 0, 0},
  };
  auto expected = xt::stack(xt::xtuple(expected_r, expected_s), 2);
  for (int i = 0; i < 2; ++i) {
    xt::xarray<double> c_output = xt::view(output, xt::all(), xt::all(), i);
    xt::xarray<double> c_expected = xt::view(expected, xt::all(), xt::all(), i);
    EXPECT_FLOATS_NEARLY_EQ(c_output, c_expected, 0.01);
  }
}

TEST(test_dg_nodal_utils, test_d_matrix_2d) {
  unsigned order = 3;
  auto rs = conversion_equilateral_xy_to_rs(generate_triangle_nodes(order));
  auto v = vandermonde_2d(order, rs);
  auto gv = grad_vandermonde_2d(order, rs);
  auto output = d_matrix_2d(v, gv);
  xt::xarray<double> expected_r = {
      {-3.0000, 4.0451, -1.5451, 0.5000, 0.0000, 0.0000, 0.0000, -0.0000, -0.0000, 0.0000},
      {-0.8090, 0.0000, 1.1180, -0.3090, 0.0000, -0.0000, -0.0000, 0.0000, 0.0000, -0.0000},
      {0.3090, -1.1180, 0.0000, 0.8090, 0.0000, -0.0000, 0.0000, 0.0000, -0.0000, -0.0000},
      {-0.5000, 1.5451, -4.0451, 3.0000, -0.0000, 0.0000, 0.0000, -0.0000, -0.0000, 0.0000},
      {-0.7090, 1.6180, -1.3090, 0.6000, -2.0000, 2.7000, -0.6180, -0.1910, -0.1910, 0.1000},
      {0.3333, -0.6211, 0.6211, -0.3333, -0.7272, -0.0000, 0.7272, -0.1061, 0.1061, -0.0000},
      {-0.6000, 1.3090, -1.6180, 0.7090, 0.6180, -2.7000, 2.0000, 0.1910, 0.1910, -0.1000},
      {0.4090, -0.1910, -0.6180, 0.6000, -1.3090, 2.7000, -1.3090, -2.0000, 1.6180, 0.1000},
      {-0.6000, 0.6180, 0.1910, -0.4090, 1.3090, -2.7000, 1.3090, -1.6180, 2.0000, -0.1000},
      {-0.5000, -0.0000, -0.0000, 0.5000, 1.5451, 0.0000, -1.5451, -4.0451, 4.0451, 0},
  };
  xt::xarray<double> expected_s = {
      {-3.0000, 0.0000, -0.0000, 0.0000, 4.0451, 0.0000, -0.0000, -1.5451, 0.0000, 0.5000},
      {-0.7090, -2.0000, -0.1910, 0.1000, 1.6180, 2.7000, -0.1910, -1.3090, -0.6180, 0.6000},
      {0.4090, -1.3090, -2.0000, 0.1000, -0.1910, 2.7000, 1.6180, -0.6180, -1.3090, 0.6000},
      {-0.5000, 1.5451, -4.0451, -0.0000, 0.0000, -0.0000, 4.0451, 0.0000, -1.5451, 0.5000},
      {-0.8090, 0.0000, 0.0000, 0.0000, 0.0000, -0.0000, 0.0000, 1.1180, -0.0000, -0.3090},
      {0.3333, -0.7272, -0.1061, -0.0000, -0.6211, -0.0000, 0.1061, 0.6211, 0.7272, -0.3333},
      {-0.6000, 1.3090, -1.6180, -0.1000, 0.6180, -2.7000, 2.0000, 0.1910, 1.3090, -0.4090},
      {0.3090, -0.0000, 0.0000, -0.0000, -1.1180, -0.0000, -0.0000, 0.0000, 0.0000, 0.8090},
      {-0.6000, 0.6180, 0.1910, -0.1000, 1.3090, -2.7000, 0.1910, -1.6180, 2.0000, 0.7090},
      {-0.5000, 0.0000, -0.0000, 0.0000, 1.5451, 0.0000, -0.0000, -4.0451, 0.0000, 3.0000},
  };
  auto expected = xt::stack(xt::xtuple(expected_r, expected_s), 2);
  for (int i = 0; i < 2; ++i) {
    xt::xarray<double> c_output = xt::view(output, xt::all(), xt::all(), i);
    xt::xarray<double> c_expected = xt::view(expected, xt::all(), xt::all(), i);
    EXPECT_FLOATS_NEARLY_EQ(c_output, c_expected, 0.01);
  }
}
