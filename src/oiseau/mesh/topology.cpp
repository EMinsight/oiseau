#include "oiseau/mesh/topology.hpp"
#include <array>
#include <vector>

using namespace oiseau::mesh;

Topology::Topology() = default;
Topology::~Topology() = default;

Topology::Topology(std::vector<std::vector<std::size_t>>&& conn, std::vector<CellType>&& cell_types)
    : m_conn(std::move(conn)), m_cell_types(std::move(cell_types)) {};

std::span<CellType> Topology::cell_types() { return m_cell_types; };

std::span<std::vector<std::size_t>> Topology::conn() { return m_conn; };
std::span<std::vector<std::size_t>> Topology::e_to_e() { return m_e_to_e; };
std::span<std::vector<std::size_t>> Topology::e_to_f() { return m_e_to_f; };

std::size_t Topology::n_cells() const { return m_conn.size(); }

void Topology::calculate_connectivity() {
  // this should be extended to 3d and for mixed cells squares/triangles
  std::vector<std::vector<std::vector<std::size_t>>> faces;
  for (int i = 0; i < m_conn.size(); i++) {
    auto cell = m_cell_types[i];
    if (cell->kind() != CellKind::Triangle) continue;
    auto _conn = m_conn[i];

    auto face_vertices = cell->get_entity_vertices(1);
    std::vector<std::vector<std::size_t>> face(face_vertices.size());
    for (int j = 0; j < face_vertices.size(); j++) {
      face[j].resize(face_vertices[j].size());
      for (int k = 0; k < face_vertices[j].size(); k++) {
        face[j][k] = _conn[face_vertices[j][k]];
      }
      std::sort(face[j].begin(), face[j].end());
    }
    faces.push_back(std::move(face));
  }
  m_e_to_e.resize(faces.size());
  m_e_to_f.resize(faces.size());
  for (int i = 0; i < m_e_to_e.size(); i++) {
    m_e_to_e[i] = std::vector<std::size_t>(faces[i].size(), i);
    m_e_to_f[i].resize(faces[i].size());
    std::iota(m_e_to_f[i].begin(), m_e_to_f[i].end(), 0);
  }

  // TODO: this is not efficient, should use a hash map
  for (int i = 0; i < faces.size(); i++) {
    for (int j = 0; j < faces[i].size(); j++) {
      for (int ii = i + 1; ii < faces.size(); ii++) {
        for (int jj = 0; jj < faces[ii].size(); jj++) {
          if (m_e_to_e[i][j] != i || m_e_to_e[ii][jj] != ii) continue;
          if (faces[i][j] == faces[ii][jj]) {
            m_e_to_e[i][j] = ii;
            m_e_to_e[ii][jj] = i;
            m_e_to_f[i][j] = jj;
            m_e_to_f[ii][jj] = j;
          }
        }
      }
    }
  }
}
