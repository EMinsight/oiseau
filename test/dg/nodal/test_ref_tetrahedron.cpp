#include <gtest/gtest.h>

#include "oiseau/dg/nodal/ref_tetrahedron.hpp"
#include "oiseau/test_macros.hpp"

TEST(test_ref_tetrahedron, get_order) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefTetrahedron(order);
    EXPECT_EQ(ref.order(), order);
  }
}

TEST(test_ref_tetrahedron, get_number_of_nodes) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefTetrahedron(order);
    unsigned n = (order + 1) * (order + 2) * (order + 3) / 6;
    EXPECT_EQ(ref.number_of_nodes(), n);
  }
}
