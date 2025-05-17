#include <gtest/gtest.h>

#include "oiseau/dg/nodal/ref_line.hpp"
#include "oiseau/test_macros.hpp"

TEST(test_ref_line, get_order) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefLine(order);
    EXPECT_EQ(ref.order(), order);
  }
}

TEST(test_ref_line, get_number_of_nodes) {
  for (unsigned order = 1; order <= 5; ++order) {
    auto ref = oiseau::dg::nodal::RefLine(order);
    EXPECT_EQ(ref.number_of_nodes(), order + 1);
  }
}
