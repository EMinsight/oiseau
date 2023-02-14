#include <fmt/core.h>
#include <fmt/ranges.h>
#include "oiseau/io/gmsh.hpp"
#include "oiseau/io/gmsh_file.hpp"

using namespace oiseau::io;
using namespace oiseau::mesh;

int main() {
  Mesh mesh = gmsh_read("demo/meshes/mesh.msh");
  auto& geometry = mesh.geometry();
  for (int i = 0; i < 50; ++i) {
    auto x = geometry.x_at(i);
    fmt::print("x = {}\n", x);
  }
}
