#include <fmt/core.h>
#include <fmt/ranges.h>
#include "oiseau/io/gmsh.hpp"
#include "oiseau/io/gmsh_file.hpp"

using namespace oiseau::io;
using namespace oiseau::mesh;

int main() {
  Mesh mesh = gmsh_read("demo/meshes/mesh.msh");
  auto& geometry = mesh.geometry();
  auto& topology = mesh.topology();

  auto cell_types = topology.cell_types();
  auto conn = topology.conn();

  fmt::print("n_nodes_per_element = {}\n", conn[0].size() );
}
