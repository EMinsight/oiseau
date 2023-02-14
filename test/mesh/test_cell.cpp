#include <gtest/gtest.h>
#include "oiseau/mesh/cell.hpp"

TEST(test_mesh, triangle_cell) {
  using namespace oiseau::mesh;
  auto tricell = TriangleCell();
  EXPECT_STREQ(tricell.name().data(), "triangle");
  EXPECT_STREQ(tricell.facet()->name().data(), "interval");
  EXPECT_STREQ(tricell.edge()->name().data(), "point");
  EXPECT_EQ(tricell.dimension(), 2);
  auto cell = TriangleCell();
}
