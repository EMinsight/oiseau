#include "oiseau/dg/nodal/ref_elements.hpp"
#include "oiseau/dg/nodal/utils.hpp"

using namespace oiseau::dg::nodal::utils;

namespace oiseau::dg::nodal {

RefLine::RefLine(unsigned order)
    : m_order(order), m_r(jacobi_gl(order, 0.0, 0.0)), m_np(order + 1) {}

xt::xarray<double>& RefLine::v() {
  static xt::xarray<double> tmp = vandermonde_1d(m_order, m_r);
  return tmp;
}

xt::xarray<double>& RefLine::gv() {
  static xt::xarray<double> tmp = grad_vandermonde_1d(m_order, m_r);
  return tmp;
}

xt::xarray<double>& RefLine::d() {
  static xt::xarray<double> tmp = d_matrix_1d(v(), gv());
  return tmp;
}

xt::xarray<double>& RefLine::r() { return m_r; }

RefTriangle::RefTriangle(unsigned order)
    : m_order(order),
      m_r(conversion_equilateral_xy_to_rs(generate_triangle_nodes(order))),
      m_np(((order + 1) * (order + 2)) / 2),
      m_nfp(order + 1) {}

xt::xarray<double>& RefTriangle::v() {
  static xt::xarray<double> tmp = vandermonde_2d(m_order, m_r);
  return tmp;
}

xt::xarray<double>& RefTriangle::gv() {
  static xt::xarray<double> tmp = grad_vandermonde_2d(m_order, m_r);
  return tmp;
}

xt::xarray<double>& RefTriangle::d() {
  static xt::xarray<double> tmp = d_matrix_2d(v(), gv());
  return tmp;
}

xt::xarray<double>& RefTriangle::r() { return m_r; }

RefTetrahedron::RefTetrahedron(unsigned order)
    : m_order(order),
      m_r(conversion_equilateral_xyz_to_rst(generate_tetrahedron_nodes(order))),
      m_np(((order + 1) * (order + 2) * (order + 3)) / 6),
      m_nfp((order + 1) * (order + 2)) {}

xt::xarray<double>& RefTetrahedron::v() {
  static xt::xarray<double> tmp = vandermonde_3d(m_order, m_r);
  return tmp;
}

xt::xarray<double>& RefTetrahedron::gv() {
  static xt::xarray<double> tmp = grad_vandermonde_3d(m_order, m_r);
  return tmp;
}

xt::xarray<double>& RefTetrahedron::d() {
  static xt::xarray<double> tmp = d_matrix_3d(v(), gv());
  return tmp;
}

xt::xarray<double>& RefTetrahedron::r() { return m_r; }

}  // namespace oiseau::dg::nodal
