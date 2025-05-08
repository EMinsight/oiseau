#include <gtest/gtest.h>
#include <oiseau/io/gmsh.hpp>

TEST(test_io, gmsh_read_from_string_3d_tetra_block) {
  std::string str =
      R"($MeshFormat
4.1 0 8
$EndMeshFormat
$Nodes
1 8 1 8
3 0 0 8
1
2
3
4
5
6
7
8
0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
1.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
1.0000000000000000e+00 1.0000000000000000e+00 0.0000000000000000e+00
0.0000000000000000e+00 1.0000000000000000e+00 0.0000000000000000e+00
0.0000000000000000e+00 0.0000000000000000e+00 1.0000000000000000e+00
1.0000000000000000e+00 0.0000000000000000e+00 1.0000000000000000e+00
1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
0.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
$EndNodes
$Elements
1 5 1 5
3 0 4 5
1 1 2 4 5
2 2 3 4 7
3 2 4 5 7
4 2 5 6 7
5 4 5 7 8
$EndElements)";
  oiseau::mesh::Mesh mesh = oiseau::io::gmsh_read_from_string(str);
  auto conn = mesh.topology().conn();
  std::vector<std::vector<size_t>> actual(conn.begin(), conn.end());
  std::vector<std::vector<size_t>> expected = {
      {0, 1, 3, 4}, {1, 2, 3, 6}, {1, 3, 4, 6}, {1, 4, 5, 6}, {3, 4, 6, 7}};
  EXPECT_EQ(actual, expected);
}
