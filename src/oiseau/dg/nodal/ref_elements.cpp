#include "oiseau/dg/nodal/ref_elements.hpp"

#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::conversion_equilateral_xy_to_rs;
using utils::conversion_equilateral_xyz_to_rst;
using utils::d_matrix_1d;
using utils::d_matrix_2d;
using utils::d_matrix_3d;
using utils::generate_hexahedron_nodes;
using utils::generate_quadrilateral_nodes;
using utils::generate_tetrahedron_nodes;
using utils::generate_triangle_nodes;
using utils::grad_vandermonde_1d;
using utils::grad_vandermonde_2d;
using utils::grad_vandermonde_2d_tensor;
using utils::grad_vandermonde_3d;
using utils::grad_vandermonde_3d_tensor;
using utils::jacobi_gl;
using utils::vandermonde_1d;
using utils::vandermonde_2d;
using utils::vandermonde_2d_tensor;
using utils::vandermonde_3d;
using utils::vandermonde_3d_tensor;

RefLine::RefLine(unsigned order) : RefElement(order) {
  this->m_np = order + 1;
  this->m_nfp = 1;
  this->m_r = jacobi_gl(this->m_order, 0.0, 0.0);
  this->m_v = vandermonde_1d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_1d(this->m_order, this->m_r);
  this->m_d = d_matrix_1d(this->m_v, this->m_gv);
}

RefTriangle::RefTriangle(unsigned order) : RefElement(order) {
  this->m_np = ((order + 1) * (order + 2)) / 2;
  this->m_nfp = order + 1;
  this->m_r = conversion_equilateral_xy_to_rs(generate_triangle_nodes(this->m_order));
  this->m_v = vandermonde_2d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_2d(this->m_order, this->m_r);
  this->m_d = d_matrix_2d(this->m_v, this->m_gv);
}

RefQuadrilateral::RefQuadrilateral(unsigned order) : RefElement(order) {
  this->m_np = (order + 1) * (order + 1);
  this->m_nfp = order + 1;
  this->m_r = generate_quadrilateral_nodes(this->m_order);
  this->m_v = vandermonde_2d_tensor(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_2d_tensor(this->m_order, this->m_r);
  this->m_d = d_matrix_2d(this->m_v, this->m_gv);
}

RefTetrahedron::RefTetrahedron(unsigned order) : RefElement(order) {
  this->m_np = ((order + 1) * (order + 2) * (order + 3)) / 6;
  this->m_nfp = ((order + 1) * (order + 2)) / 2;
  this->m_r = conversion_equilateral_xyz_to_rst(generate_tetrahedron_nodes(this->m_order));
  this->m_v = vandermonde_3d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}

RefHexahedron::RefHexahedron(unsigned order) : RefElement(order) {
  this->m_np = (order + 1) * (order + 1) * (order + 1);
  this->m_nfp = (order + 1) * (order + 1);
  this->m_r = generate_hexahedron_nodes(this->m_order);
  this->m_v = vandermonde_3d_tensor(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d_tensor(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}

std::shared_ptr<RefElement> get_ref_element(RefElementType type, unsigned order) {
  using Key = std::pair<RefElementType, unsigned>;

  struct KeyHash {
    std::size_t operator()(const Key& k) const {
      return std::hash<int>()(static_cast<int>(k.first)) ^ std::hash<unsigned>()(k.second);
    }
  };

  static std::unordered_map<Key, std::shared_ptr<RefElement>, KeyHash> cache;

  Key key{type, order};
  auto it = cache.find(key);
  if (it != cache.end()) {
    return it->second;
  }

  std::shared_ptr<RefElement> elem;
  switch (type) {
  case RefElementType::Line:
    elem = std::make_shared<RefLine>(order);
    break;
  case RefElementType::Triangle:
    elem = std::make_shared<RefTriangle>(order);
    break;
  case RefElementType::Quadrilateral:
    elem = std::make_shared<RefQuadrilateral>(order);
    break;
  case RefElementType::Tetrahedron:
    elem = std::make_shared<RefTetrahedron>(order);
    break;
  case RefElementType::Hexahedron:
    elem = std::make_shared<RefHexahedron>(order);
    break;
  default:
    throw std::invalid_argument("Unknown element type");
  }

  cache[key] = elem;
  return elem;
}

}  // namespace oiseau::dg::nodal
