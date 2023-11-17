#include "oiseau/mesh/topology.hpp"
#include <array>
#include <vector>

using namespace oiseau::mesh;

Topology::Topology(){};
Topology::~Topology(){};

Topology::Topology(std::vector<std::vector<std::size_t>> &&conn, std::vector<CellType> &&cell_types)
    : m_conn(std::move(conn)), m_cell_types(std::move(cell_types)){};

std::span<CellType> Topology::cell_types() { return m_cell_types; };

std::span<std::vector<std::size_t>> Topology::conn() { return m_conn; };
