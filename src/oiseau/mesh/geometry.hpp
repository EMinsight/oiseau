#pragma once
#include <cstddef>
#include <span>
#include <vector>

namespace oiseau::mesh {
class Geometry {
 public:
  Geometry();
  Geometry(std::vector<double> &&x, unsigned dim);
  Geometry(Geometry &&) = default;
  Geometry(const Geometry &) = default;
  Geometry &operator=(Geometry &&) = default;
  Geometry &operator=(const Geometry &) = default;
  ~Geometry();

  std::span<double> x();
  std::span<double> x_at(std::size_t pos);
  unsigned dim() const;

 private:
  std::vector<double> m_x;
  unsigned m_dim = 3;
};
}  // namespace oiseau::mesh
