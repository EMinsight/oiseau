#pragma once

#include <oiseau/dg/nodal/utils.hpp>
#include <xtensor/xarray.hpp>

namespace oiseau::dg::nodal {

class DGElement {
 public:
  explicit DGElement() = default;
  virtual ~DGElement() = default;

  virtual xt::xarray<double> &v() = 0;
  virtual xt::xarray<double> &gv() = 0;
  virtual xt::xarray<double> &d() = 0;
};

class RefLine : DGElement {
 private:
  const static unsigned int n_fp = 1;
  const static unsigned int n_faces = 2;

 public:
  explicit RefLine(unsigned order);
  RefLine(const RefLine &) = default;
  RefLine &operator=(RefLine &&) = default;
  RefLine &operator=(const RefLine &) = default;
  ~RefLine() = default;

  xt::xarray<double> &v() override;
  xt::xarray<double> &gv() override;
  xt::xarray<double> &d() override;
  xt::xarray<double> &r() { return m_r; };

 private:
  xt::xarray<double> m_r;
  unsigned m_order;
  unsigned m_np;
};

}  // namespace oiseau::dg::nodal
