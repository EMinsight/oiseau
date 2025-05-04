#include <fmt/core.h>
#include <fmt/ranges.h>
#include "oiseau/io/gmsh.hpp"
#include "oiseau/mesh/dgmesh.hpp"
#include "oiseau/plotting/triplot.hpp"

using namespace oiseau::io;
using namespace oiseau::mesh;

int main() {
  Mesh mesh = gmsh_read("demo/meshes/mesh2d_split_triangles_quads.msh");
  auto& geometry = mesh.geometry();
  auto& topology = mesh.topology();

  auto cell_types = topology.cell_types();
  auto conn = topology.conn();

  plt::scoped_interpreter guard{};

  auto [fig, ax] =
      plt::subplots(1, 1, "constrained_layout"_a = true, "figsize"_a = std::array<double, 2>{8, 8});

  oiseau::plotting::triplot(ax, mesh);

  plt::show();

  //
  // auto dgmesh = DGMesh(mesh, 5);
  //
  // fmt::print("number of elements = {}\n", dgmesh.mesh().topology().n_cells());
  // fmt::print("order of the first element = {}\n", dgmesh.order_at(0));
  // topology.calculate_connectivity();
  //
  // auto e_to_f = topology.e_to_f();
  // fmt::print("{}", e_to_f);
}
