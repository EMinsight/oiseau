#include "oiseau/dg/nodal/ref_hexahedron.hpp"

#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::d_matrix_3d;
using utils::generate_hexahedron_nodes;
using utils::grad_vandermonde_3d_tensor;
using utils::vandermonde_3d_tensor;

RefHexahedron::RefHexahedron(unsigned order) : RefElement(order) {
  this->m_np = (order + 1) * (order + 1) * (order + 1);
  this->m_nfp = (order + 1) * (order + 1);
  this->m_r = generate_hexahedron_nodes(this->m_order);
  this->m_v = vandermonde_3d_tensor(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d_tensor(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}
}  // namespace oiseau::dg::nodal
