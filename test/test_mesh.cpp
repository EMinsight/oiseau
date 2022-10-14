#include "oiseau/mesh/cell.hpp"
#include <gtest/gtest.h>

TEST(test_mesh, triangle_cell) {
    using namespace oiseau::mesh;
    auto tricell = TriangleCell();
    EXPECT_STREQ(tricell.name().c_str(), "triangle");
    EXPECT_EQ(tricell.dimension(), 2);
}
