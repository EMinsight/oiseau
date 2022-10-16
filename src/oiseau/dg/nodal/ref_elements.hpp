#include <xtensor/xarray.hpp>

class RefLine {
 private:
  unsigned int m_order, n_p;
  xt::xarray<double> r;
  const static unsigned int n_fp = 1;
  const static unsigned int n_faces = 2;

 public:
  RefLine() : m_order(3), n_p(3 + 1) {}
  RefLine(unsigned int order) : m_order(order), n_p(order + 1) {}
  RefLine(RefLine &&) = default;
  RefLine(const RefLine &) = default;
  RefLine &operator=(RefLine &&) = default;
  RefLine &operator=(const RefLine &) = default;
  ~RefLine();

 private:
};
