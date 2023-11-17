#pragma once
#include "oiseau/mesh/cell.hpp"

namespace oiseau::mesh {

class Topology {
 public:
  Topology();
  Topology(std::vector<std::vector<std::size_t>> &&conn, std::vector<CellType> &&cell_types);
  Topology(Topology &&) = default;
  Topology(const Topology &) = default;
  Topology &operator=(Topology &&) = default;
  Topology &operator=(const Topology &) = default;
  ~Topology();
  std::span<CellType> cell_types();
  std::span<std::vector<std::size_t>> conn();

 private:
  std::vector<std::vector<std::size_t>> m_conn;
  std::vector<CellType> m_cell_types;
};

}  // namespace oiseau::mesh
