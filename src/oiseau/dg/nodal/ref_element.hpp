#pragma once

#include <memory>
#include <xtensor/containers/xarray.hpp>

#include "xtensor/core/xtensor_forward.hpp"

namespace oiseau::dg::nodal {

enum class RefElementType { Line, Triangle, Quadrilateral, Tetrahedron, Hexahedron };

class RefElement {
 public:
  virtual ~RefElement() = default;

  const xt::xarray<double>& v() const { return m_v; }
  const xt::xarray<double>& gv() const { return m_gv; }
  const xt::xarray<double>& d() const { return m_d; }
  const xt::xarray<double>& r() const { return m_r; }

  unsigned get_order() const { return m_order; }
  unsigned get_np() const { return m_np; }
  unsigned get_nfp() const { return m_nfp; }

 protected:
  explicit RefElement(unsigned order_val) : m_order(order_val) {}

  unsigned m_order;
  unsigned m_np{};
  unsigned m_nfp{};
  xt::xarray<double> m_v;
  xt::xarray<double> m_gv;
  xt::xarray<double> m_d;
  xt::xarray<double> m_r;
};

std::shared_ptr<RefElement> get_ref_element(RefElementType type, unsigned order);

}  // namespace oiseau::dg::nodal
