#include <fmt/core.h>
#include <fmt/ranges.h>

#include <ranges>

#include "oiseau/io/gmsh.hpp"
#include "oiseau/plotting/triplot.hpp"

using namespace oiseau::io;
using namespace oiseau::mesh;

void two_dimensional() {
  Mesh mesh = gmsh_read_from_path("demo/meshes/mesh2d_split_triangles_quads.msh");
  auto& geometry = mesh.geometry();
  auto& topology = mesh.topology();

  auto cell_types = topology.cell_types();
  auto conn = topology.conn();

  plt::scoped_interpreter guard{};

  auto [fig, ax] =
      plt::subplots(1, 1, "constrained_layout"_a = true, "figsize"_a = std::array<double, 2>{8, 8});

  oiseau::plotting::triplot(ax, mesh);

  plt::show();
}

void three_dimensional() {
  Mesh mesh = gmsh_read_from_path("demo/meshes/mesh3d_tetra_hexa_block.msh");
  auto& geometry = mesh.geometry();
  auto& topology = mesh.topology();

  auto cell_types = topology.cell_types();
  auto conn = topology.conn();

  for (auto [ct, vertices] : std::views::zip(cell_types, conn)) {
    std::cout << ct->name() << std::endl;
    fmt::print("{}", vertices);
  }
}

int main() {
  two_dimensional();
  three_dimensional();
}
