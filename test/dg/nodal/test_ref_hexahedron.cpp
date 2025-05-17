#include <gtest/gtest.h>

#include "oiseau/dg/nodal/ref_hexahedron.hpp"
#include "oiseau/test_macros.hpp"

TEST(test_ref_hexahedron, get_order) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefHexahedron(order);
    EXPECT_EQ(ref.order(), order);
  }
}

TEST(test_ref_hexahedron, get_number_of_nodes) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefHexahedron(order);
    unsigned n = (order + 1) * (order + 1) * (order + 1);
    EXPECT_EQ(ref.number_of_nodes(), n);
  }
}
