#include "oiseau/dg/nodal/ref_tetrahedron.hpp"

#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::conversion_equilateral_xyz_to_rst;
using utils::d_matrix_3d;
using utils::generate_tetrahedron_nodes;
using utils::grad_vandermonde_3d;
using utils::vandermonde_3d;

RefTetrahedron::RefTetrahedron(unsigned order) : RefElement(order) {
  this->m_np = ((order + 1) * (order + 2) * (order + 3)) / 6;
  this->m_nfp = ((order + 1) * (order + 2)) / 2;
  this->m_r = conversion_equilateral_xyz_to_rst(generate_tetrahedron_nodes(this->m_order));
  this->m_v = vandermonde_3d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}
}  // namespace oiseau::dg::nodal
