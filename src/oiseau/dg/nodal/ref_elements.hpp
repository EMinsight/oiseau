#pragma once

#include <xtensor/containers/xarray.hpp>

namespace oiseau::dg::nodal {

class DGElement {
 public:
  virtual ~DGElement() = default;

  virtual xt::xarray<double>& v() = 0;
  virtual xt::xarray<double>& gv() = 0;
  virtual xt::xarray<double>& d() = 0;
  virtual xt::xarray<double>& r() = 0;
};

class RefLine : public DGElement {
 public:
  explicit RefLine(unsigned order);
  RefLine(const RefLine&) = default;
  RefLine& operator=(RefLine&&) = default;
  RefLine& operator=(const RefLine&) = default;
  ~RefLine() override = default;

  xt::xarray<double>& v() override;
  xt::xarray<double>& gv() override;
  xt::xarray<double>& d() override;
  xt::xarray<double>& r() override;

 private:
  static constexpr unsigned m_nfp = 1;
  static constexpr unsigned m_nfaces = 2;
  unsigned m_order;
  unsigned m_np;
  xt::xarray<double> m_r;
};

class RefTriangle : public DGElement {
 public:
  explicit RefTriangle(unsigned order);
  RefTriangle(const RefTriangle&) = default;
  RefTriangle& operator=(RefTriangle&&) = default;
  RefTriangle& operator=(const RefTriangle&) = default;
  ~RefTriangle() override = default;

  xt::xarray<double>& v() override;
  xt::xarray<double>& gv() override;
  xt::xarray<double>& d() override;
  xt::xarray<double>& r() override;

 private:
  static constexpr unsigned m_nfaces = 3;
  unsigned m_order;
  unsigned m_np;
  unsigned m_nfp;
  xt::xarray<double> m_r;
};

class RefTetrahedron : public DGElement {
 public:
  explicit RefTetrahedron(unsigned order);
  RefTetrahedron(const RefTetrahedron&) = default;
  RefTetrahedron& operator=(RefTetrahedron&&) = default;
  RefTetrahedron& operator=(const RefTetrahedron&) = default;
  ~RefTetrahedron() override = default;

  xt::xarray<double>& v() override;
  xt::xarray<double>& gv() override;
  xt::xarray<double>& d() override;
  xt::xarray<double>& r() override;

 private:
  static constexpr unsigned m_nfaces = 4;
  unsigned m_order;
  unsigned m_np;
  unsigned m_nfp;
  xt::xarray<double> m_r;
};

}  // namespace oiseau::dg::nodal
