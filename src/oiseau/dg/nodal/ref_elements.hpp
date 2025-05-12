#pragma once

#include <xtensor/containers/xarray.hpp>

namespace oiseau::dg::nodal {

enum class ElementType { Line, Triangle, Quadrilateral, Tetrahedron, Hexahedron };

class DGElement {
 public:
  virtual ~DGElement() = default;

  const xt::xarray<double>& v() const { return m_v; }
  const xt::xarray<double>& gv() const { return m_gv; }
  const xt::xarray<double>& d() const { return m_d; }
  const xt::xarray<double>& r() const { return m_r; }

  unsigned get_order() const { return m_order; }
  unsigned get_np() const { return m_np; }
  unsigned get_nfp() const { return m_nfp; }

 protected:
  explicit DGElement(unsigned order_val) : m_order(order_val) {}

  unsigned m_order;
  unsigned m_np{};
  unsigned m_nfp{};
  xt::xarray<double> m_v;
  xt::xarray<double> m_gv;
  xt::xarray<double> m_d;
  xt::xarray<double> m_r;
};

class RefLine : public DGElement {
 public:
  explicit RefLine(unsigned order);
};

class RefTriangle : public DGElement {
 public:
  explicit RefTriangle(unsigned order);
};

class RefQuadrilateral : public DGElement {
 public:
  explicit RefQuadrilateral(unsigned order);
};

class RefTetrahedron : public DGElement {
 public:
  explicit RefTetrahedron(unsigned order);
};

class RefHexahedron : public DGElement {
 public:
  explicit RefHexahedron(unsigned order);
};

std::shared_ptr<DGElement> get_ref_element(ElementType type, unsigned order);

}  // namespace oiseau::dg::nodal
