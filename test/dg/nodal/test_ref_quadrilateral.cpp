#include <gtest/gtest.h>

#include "oiseau/dg/nodal/ref_quadrilateral.hpp"
#include "oiseau/test_macros.hpp"

TEST(test_ref_quadrilateral, get_order) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefQuadrilateral(order);
    EXPECT_EQ(ref.order(), order);
  }
}

TEST(test_ref_quadrilateral, get_number_of_nodes) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefQuadrilateral(order);
    unsigned n = (order + 1) * (order + 1);
    EXPECT_EQ(ref.number_of_nodes(), n);
  }
}
