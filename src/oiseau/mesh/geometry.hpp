#pragma once
#include <span>
#include <vector>

namespace oiseau::mesh {
class Geometry {
 public:
  Geometry();
  Geometry(Geometry &&) = default;
  Geometry(const Geometry &) = default;
  Geometry &operator=(Geometry &&) = default;
  Geometry &operator=(const Geometry &) = default;
  ~Geometry();

  std::span<double> x();

 private:
  std::vector<double> m_x;
};
}  // namespace oiseau::mesh
