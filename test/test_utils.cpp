#include <gtest/gtest.h>
#include <oiseau/utils/math.h>

#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh)                                                              \
    EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";                                                \
    for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) {                                      \
        EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;                                        \
    }

TEST(test_utils, test_jacobi_p) {
    unsigned n = 2;
    double alpha = 1.0, beta = 2.0;
    std::vector<double> input = {0.1, 0.3, 0.7, 0.9};
    std::vector<double> expected = {-0.77365811, -0.6641136, 0.70519279, 1.96495468};
    auto output = oiseau::utils::jacobi_p(n, alpha, beta, input);
    EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.0001);
}

TEST(test_utils, test_grad_jacobi_p) {
    unsigned n = 2;
    double alpha = 1.0, beta = 2.0;
    std::vector<double> input = {0.1, 0.3, 0.7, 0.9};
    std::vector<double> expected = {-0.41079192, 1.50623703, 5.34029494, 7.25732389};
    auto output = oiseau::utils::grad_jacobi_p(n, alpha, beta, input);
    EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.0001);
}

TEST(test_utils, test_jacobi_gq) {
    unsigned n = 3;
    double alpha = 1.0, beta = 2.0;
    auto [x, w] = oiseau::utils::jacobi_gq(n, alpha, beta);
    xt::xarray<double> x_expected = {-0.65077886, -0.15637043, 0.37348938, 0.79729627};
    xt::xarray<double> w_expected = {0.08666291, 0.44123335, 0.59015336, 0.21528371};
    EXPECT_FLOATS_NEARLY_EQ(x, x_expected, 0.0001);
    EXPECT_FLOATS_NEARLY_EQ(w, w_expected, 0.0001);
}

TEST(test_utils, test_jacobi_gl) {
    unsigned n = 4;
    double alpha = 1.0, beta = 2.0;
    auto output = oiseau::utils::jacobi_gl(n, alpha, beta);
    xt::xarray<double> expected = {-1., -0.4611587, 0.10438533, 0.62950065, 1.};
    EXPECT_FLOATS_NEARLY_EQ(output, expected, 0.0001);
}
