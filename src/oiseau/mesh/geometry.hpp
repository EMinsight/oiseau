#pragma once
#include <span>
#include <vector>

namespace oiseau::mesh {
class Geometry {
 public:
  Geometry();
  Geometry(std::vector<double> &&x, int dim);
  Geometry(Geometry &&) = default;
  Geometry(const Geometry &) = default;
  Geometry &operator=(Geometry &&) = default;
  Geometry &operator=(const Geometry &) = default;
  ~Geometry();

  std::span<double> x();
  std::span<double> x_at(std::size_t pos);

 private:
  std::vector<double> m_x;
  int m_dim;
};
}  // namespace oiseau::mesh
