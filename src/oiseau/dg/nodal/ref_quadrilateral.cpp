#include "oiseau/dg/nodal/ref_quadrilateral.hpp"

#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::d_matrix_2d;
using utils::generate_quadrilateral_nodes;
using utils::grad_vandermonde_2d_tensor;
using utils::vandermonde_2d_tensor;

RefQuadrilateral::RefQuadrilateral(unsigned order) : RefElement(order) {
  this->m_np = (order + 1) * (order + 1);
  this->m_nfp = order + 1;
  this->m_r = generate_quadrilateral_nodes(this->m_order);
  this->m_v = vandermonde_2d_tensor(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_2d_tensor(this->m_order, this->m_r);
  this->m_d = d_matrix_2d(this->m_v, this->m_gv);
}
}  // namespace oiseau::dg::nodal
