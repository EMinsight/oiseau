#include "oiseau/plotting/triplot.hpp"

#include <xtensor/containers/xadapt.hpp>
#include <xtensor/views/xview.hpp>

namespace oiseau::plotting {

void triplot(plt::AxesSubPlot &ax, oiseau::mesh::Mesh &mesh) {
  auto topology = mesh.topology();
  auto geometry = mesh.geometry();
  auto connectivity = topology.conn();
  auto x = geometry.x();

  std::vector<std::size_t> shape = {x.size() / 3, 3};
  auto coords = xt::adapt(x.data(), x.size(), xt::no_ownership(), shape);

  for (std::size_t i = 0; i < connectivity.size(); ++i) {
    auto cell = topology.cell_types()[i];
    auto conn = connectivity[i];

    auto face_vertices = cell->get_entity_vertices(1);
    for (const auto &face_vertice : face_vertices) {
      std::vector<std::size_t> temp(face_vertice.size());
      std::ranges::transform(face_vertice, temp.begin(),
                             [&conn](std::size_t idx) { return conn[idx]; });

      auto co = xt::view(coords, xt::keep(temp));
      auto xx = xt::col(co, 0);
      auto yy = xt::col(co, 1);
      ax.plot(xx, yy, "color"_a = "k");
    }
  }
}

}  // namespace oiseau::plotting
