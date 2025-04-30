#pragma once

#include <oiseau/dg/nodal/utils.hpp>
#include <xtensor/containers/xarray.hpp>

namespace oiseau::dg::nodal {

class DGElement {
 public:
  explicit DGElement() = default;
  virtual ~DGElement() = default;

  virtual xt::xarray<double> &v() = 0;
  virtual xt::xarray<double> &gv() = 0;
  virtual xt::xarray<double> &d() = 0;
  virtual xt::xarray<double> &r() = 0;
};

class RefLine : DGElement {
 private:
  const static unsigned int m_nfp = 1;
  const static unsigned int m_nfaces = 2;

 public:
  explicit RefLine(unsigned order);
  RefLine(const RefLine &) = default;
  RefLine &operator=(RefLine &&) = default;
  RefLine &operator=(const RefLine &) = default;
  ~RefLine() = default;

  xt::xarray<double> &v() override;
  xt::xarray<double> &gv() override;
  xt::xarray<double> &d() override;
  xt::xarray<double> &r() override;

 private:
  xt::xarray<double> m_r;
  unsigned m_order;
  unsigned m_np;
};

class RefTriangle : DGElement {
 private:
  const static unsigned int m_nfaces = 3;

 public:
  explicit RefTriangle(unsigned order);
  RefTriangle(const RefTriangle &) = default;
  RefTriangle &operator=(RefTriangle &&) = default;
  RefTriangle &operator=(const RefTriangle &) = default;
  ~RefTriangle() = default;

  xt::xarray<double> &v() override;
  xt::xarray<double> &gv() override;
  xt::xarray<double> &d() override;
  xt::xarray<double> &r() override;

 private:
  xt::xarray<double> m_r;
  unsigned m_order;
  unsigned m_np;
  unsigned int m_nfp = 1;
};

class RefTetrahedron : DGElement {
 private:
  const static unsigned int m_nfaces = 4;

 public:
  explicit RefTetrahedron(unsigned order);
  RefTetrahedron(const RefTetrahedron &) = default;
  RefTetrahedron &operator=(RefTetrahedron &&) = default;
  RefTetrahedron &operator=(const RefTetrahedron &) = default;
  ~RefTetrahedron() = default;

  xt::xarray<double> &v() override;
  xt::xarray<double> &gv() override;
  xt::xarray<double> &d() override;
  xt::xarray<double> &r() override;

 private:
  xt::xarray<double> m_r;
  unsigned m_order;
  unsigned m_np;
  unsigned int m_nfp = 1;
};

}  // namespace oiseau::dg::nodal
