#include <fmt/core.h>
#include <fmt/ranges.h>
#include "oiseau/io/gmsh.hpp"
#include "oiseau/mesh/dgmesh.hpp"

using namespace oiseau::io;
using namespace oiseau::mesh;

int main() {
  Mesh mesh = gmsh_read("demo/meshes/mesh.msh");
  auto& geometry = mesh.geometry();
  auto& topology = mesh.topology();

  auto cell_types = topology.cell_types();
  auto conn = topology.conn();

  auto dgmesh = DGMesh(mesh, 5);

  fmt::print("number of elements = {}\n", dgmesh.mesh().topology().n_cells());
  fmt::print("order of the first element = {}\n", dgmesh.order_at(0));
  topology.calculate_connectivity();

  auto e_to_f = topology.e_to_f();
  fmt::print("{}", e_to_f);
}
