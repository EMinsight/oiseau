#include "oiseau/dg/nodal/ref_line.hpp"

#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::d_matrix_1d;
using utils::grad_vandermonde_1d;
using utils::jacobi_gl;
using utils::vandermonde_1d;

RefLine::RefLine(unsigned order) : RefElement(order) {
  this->m_np = order + 1;
  this->m_nfp = 1;
  this->m_r = jacobi_gl(this->m_order, 0.0, 0.0);
  this->m_v = vandermonde_1d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_1d(this->m_order, this->m_r);
  this->m_d = d_matrix_1d(this->m_v, this->m_gv);
}
}  // namespace oiseau::dg::nodal
