#include "oiseau/dg/nodal/ref_elements.hpp"

namespace oiseau::dg::nodal {
RefLine::RefLine(unsigned order) : m_order(order) {
  m_r = oiseau::dg::nodal::utils::jacobi_gl(m_order, 0.0, 0.0);
  m_np = order + 1;
}

xt::xarray<double> &RefLine::v() {
  using namespace oiseau::dg::nodal::utils;
  static auto tmp = vandermonde_1d(m_order, m_r);
  return tmp;
}

xt::xarray<double> &RefLine::gv() {
  using namespace oiseau::dg::nodal::utils;
  static auto tmp = grad_vandermonde_1d(m_order, m_r);
  return tmp;
}

xt::xarray<double> &RefLine::d() {
  using namespace oiseau::dg::nodal::utils;
  static auto tmp = d_matrix_1d(v(), gv());
  return tmp;
}

RefTriangle::RefTriangle(unsigned order) : m_order(order) {
  using namespace oiseau::dg::nodal::utils;
  m_r = conversion_equilateral_xy_to_rs(generate_triangle_nodes(order));
  m_np = m_order + 1;
  m_nfp = m_order + 1;
  m_np = ((m_order + 1) * (m_order + 2)) / 2;
}

xt::xarray<double> &RefTriangle::v() {
  using namespace oiseau::dg::nodal::utils;
  static auto tmp = vandermonde_2d(m_order, m_r);
  return tmp;
}

xt::xarray<double> &RefTriangle::gv() {
  using namespace oiseau::dg::nodal::utils;
  static auto tmp = grad_vandermonde_2d(m_order, m_r);
  return tmp;
}

xt::xarray<double> &RefTriangle::d() {
  using namespace oiseau::dg::nodal::utils;
  static auto tmp = d_matrix_2d(v(), gv());
  return tmp;
}

}  // namespace oiseau::dg::nodal
