#include "oiseau/plotting/triplot.hpp"

namespace oiseau::plotting {

void triplot(plt::AxesSubPlot &ax, oiseau::mesh::Mesh &mesh) {
  std::vector<std::vector<std::vector<std::size_t>>> faces;
  auto topology = mesh.topology();
  auto geometry = mesh.geometry();
  auto connectivity = topology.conn();
  auto x = geometry.x();

  std::vector<std::size_t> shape = {x.size() / 3, 3};
  auto coords = xt::adapt(x.data(), x.size(), xt::no_ownership(), shape);

  for (int i = 0; i < connectivity.size(); i++) {
    auto cell = topology.cell_types()[i];
    auto conn = connectivity[i];

    auto face_vertices = cell->get_entity_vertices(1);
    std::vector<std::vector<std::size_t>> faces;
    for (int j = 0; j < face_vertices.size(); j++) {
      std::vector<std::size_t> temp(2);
      for (int k = 0; k < face_vertices[j].size(); k++) {
        temp[k] = conn[face_vertices[j][k]];
      }
      auto co = xt::view(coords, xt::keep(temp));
      auto xx = xt::col(co, 0);
      auto yy = xt::col(co, 1);
      ax.plot(xx, yy, "color"_a = "k");
    }
  }
}
}  // namespace oiseau::plotting
