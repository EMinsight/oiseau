#include <gtest/gtest.h>

#include "oiseau/dg/nodal/ref_triangle.hpp"
#include "oiseau/test_macros.hpp"

TEST(test_ref_triangle, get_order) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefTriangle(order);
    EXPECT_EQ(ref.order(), order);
  }
}

TEST(test_ref_triangle, get_number_of_nodes) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefTriangle(order);
    unsigned n = (order + 1) * (order + 2) / 2;
    EXPECT_EQ(ref.number_of_nodes(), n);
  }
}
