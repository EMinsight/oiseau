#include "oiseau/dg/nodal/utils.hpp"
#include "oiseau/io/gmsh.hpp"
#include "oiseau/plotting/pyplot.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/core/xmath.hpp"
#include "xtensor/views/xindex_view.hpp"

using namespace oiseau::io;
using namespace oiseau::mesh;

using namespace oiseau::dg::nodal::utils;

int main() {
  plt::scoped_interpreter guard{};

  Mesh mesh = gmsh_read_from_path("demo/meshes/mesh.msh");

  auto x = mesh.geometry().x();
  std::vector<std::size_t> shape = {x.size() / 3, 3};
  auto coords = xt::adapt(x.data(), x.size(), xt::no_ownership(), shape);
  auto x_coord = xt::col(coords, 0);
  auto y_coord = xt::col(coords, 1);
  auto z_coord = xt::col(coords, 2);

  auto conn = mesh.topology().conn();
  auto cells = mesh.topology().cell_types();

  std::vector<double> flat;
  for (int i = 0; i < conn.size(); i++) {
    if (cells[i]->kind() == CellKind::Triangle) {
      flat.insert(flat.end(), conn[i].begin(), conn[i].end());
    }
  }
  std::size_t rows = flat.size() / 3;
  std::size_t cols = 3;
  xt::xarray<double> connectivity = xt::adapt(flat, {rows, cols});

  xt::xarray<double> centroids = xt::zeros<double>({rows, cols});

  for (size_t e = 0; e < rows; ++e) {
    auto indices = xt::view(connectivity, e);
    xt::xarray<double> element_coords = xt::view(coords, xt::keep(indices));
    auto centroid = xt::mean(element_coords, {0});
    xt::view(centroids, e) = centroid;
  }

  auto [fig, ax] =
      plt::subplots(1, 1, "constrained_layout"_a = true, "figsize"_a = std::array<double, 2>{8, 8});
  ax.scatter(x_coord, y_coord, "s"_a = 1, "label"_a = "scatter");
  ax.scatter(xt::col(centroids, 0), xt::col(centroids, 1), "s"_a = 0.1, "label"_a = "scatter",
             "color"_a = "red");
  ax.triplot(x_coord, y_coord, connectivity, "lw"_a = 0.1);

  // for every centroid row
  // for (std::size_t i = 0; i < centroids.shape()[0]; ++i) {
  //   auto row = xt::row(centroids, i);
  //   ax.text(row(0), row(1), std::to_string(i), "fontsize"_a = 4, "color"_a = "red",
  //   "rasterized"_a=true);
  // }
  plt::show();
}

// {
// Example of 3d plot
// plt::Figure fig = plt::figure("constrained_layout"_a = true);
// auto ax = fig.add_subplot("projection"_a = "3d");
// }
