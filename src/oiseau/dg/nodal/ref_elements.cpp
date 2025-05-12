#include "oiseau/dg/nodal/ref_elements.hpp"

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
using utils::grad_vandermonde_3d;
using utils::jacobi_gl;
using utils::vandermonde_1d;
using utils::vandermonde_2d;
using utils::vandermonde_3d;

RefLine::RefLine(unsigned order) : DGElement(order) {
  this->m_np = order + 1;
  this->m_nfp = 1;
  this->m_r = jacobi_gl(this->m_order, 0.0, 0.0);
  this->m_v = vandermonde_1d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_1d(this->m_order, this->m_r);
  this->m_d = d_matrix_1d(this->m_v, this->m_gv);
}

RefTriangle::RefTriangle(unsigned order) : DGElement(order) {
  this->m_np = ((order + 1) * (order + 2)) / 2;
  this->m_nfp = order + 1;
  this->m_r = conversion_equilateral_xy_to_rs(generate_triangle_nodes(this->m_order));
  this->m_v = vandermonde_2d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_2d(this->m_order, this->m_r);
  this->m_d = d_matrix_2d(this->m_v, this->m_gv);
}

RefQuadrilateral::RefQuadrilateral(unsigned order)  // New Implementation
    : DGElement(order) {
  this->m_np = (order + 1) * (order + 1);
  this->m_nfp = order + 1;  // A face of a quadrilateral is a line
  this->m_r = generate_quadrilateral_nodes(this->m_order);
  this->m_v = vandermonde_2d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_2d(this->m_order, this->m_r);
  this->m_d = d_matrix_2d(this->m_v, this->m_gv);  // Reuses generic 2D D-matrix calculator
}

RefTetrahedron::RefTetrahedron(unsigned order) : DGElement(order) {
  this->m_np = ((order + 1) * (order + 2) * (order + 3)) / 6;
  this->m_nfp = ((order + 1) * (order + 2)) / 2;
  this->m_r = conversion_equilateral_xyz_to_rst(generate_tetrahedron_nodes(this->m_order));
  this->m_v = vandermonde_3d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}

RefHexahedron::RefHexahedron(unsigned order) : DGElement(order) {
  this->m_np = (order + 1) * (order + 1) * (order + 1);
  this->m_nfp = (order + 1) * (order + 1);
  this->m_r = generate_hexahedron_nodes(this->m_order);
  this->m_v = vandermonde_3d(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}

}  // namespace oiseau::dg::nodal
