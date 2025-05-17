#include "oiseau/dg/nodal/ref_triangle.hpp"

#include "oiseau/dg/nodal/ref_elements.hpp"
#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::conversion_equilateral_xy_to_rs;
using utils::d_matrix_2d;
using utils::generate_triangle_nodes;
using utils::grad_vandermonde_2d;
using utils::vandermonde_2d;

RefTriangle::RefTriangle(unsigned order) : RefElement(order) {
  this->m_np = ((order + 1) * (order + 2)) / 2;
  this->m_nfp = order + 1;
  this->m_r = conversion_equilateral_xy_to_rs(generate_triangle_nodes(this->m_order));
  this->m_v = vandermonde_2d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_2d(this->m_order, this->m_r);
  this->m_d = d_matrix_2d(this->m_v, this->m_gv);
}
}  // namespace oiseau::dg::nodal
