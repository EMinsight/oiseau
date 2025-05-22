#include "oiseau/dg/function_space.hpp"

#include <array>
#include <cstddef>
#include <span>
#include <stdexcept>
#include <vector>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/containers/xadapt.hpp>
#include <xtensor/containers/xbuffer_adaptor.hpp>
#include <xtensor/io/xio.hpp>
#include <xtensor/views/xslice.hpp>
#include <xtensor/views/xview.hpp>

#include "oiseau/dg/nodal/element.hpp"
#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/mesh/cell.hpp"
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::dg {

FunctionSpace::FunctionSpace(const mesh::Mesh& mesh, const std::vector<unsigned>& orders)
    : m_mesh(mesh), m_orders(orders) {
  m_elements.reserve(orders.size());

  auto topology = mesh.topology();
  auto geometry = mesh.geometry();
  auto cell_types = topology.cell_types();

  std::array<std::size_t, 2> shape = {geometry.x().size() / geometry.dim(), geometry.dim()};
  auto nodes = xt::adapt(geometry.x().data(), geometry.x().size(), xt::no_ownership(), shape);

  for (std::size_t i = 0; i < cell_types.size(); ++i) {
    const auto& cell_type = cell_types[i];
    mesh::CellKind kind = cell_type->kind();

    nodal::RefElementType ref_type;
    switch (kind) {
    case mesh::CellKind::Triangle:
      ref_type = nodal::RefElementType::Triangle;
      break;
    case mesh::CellKind::Quadrilateral:
      ref_type = nodal::RefElementType::Quadrilateral;
      // FIX: wrong quadrilateral ordering
      break;
    default:
      throw std::runtime_error("Unsupported cell type");
    }

    auto interp_elem = nodal::get_ref_element(ref_type, 1);
    auto ref_elem = nodal::get_ref_element(ref_type, orders[i]);
    auto x_view = xt::view(nodes, xt::keep(topology.conn()[i]), xt::all());

    auto inv_v = xt::linalg::inv(interp_elem->v());
    auto v = interp_elem->vandermonde(ref_elem->r());
    auto interp_x = xt::linalg::dot(xt::linalg::dot(v, inv_v), x_view);

    m_elements.emplace_back(ref_elem, interp_x);
  }
  // TODO(tiagovla): clean up this mess, introduce proper api
}
std::span<const nodal::Element> FunctionSpace::elements() const { return {m_elements}; }
std::span<const unsigned> FunctionSpace::orders() const { return {m_orders}; }

}  // namespace oiseau::dg
