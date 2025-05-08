#include "oiseau/io/gmsh.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "oiseau/io/gmsh_file.hpp"
#include "oiseau/mesh/cell.hpp"
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::mesh {
CellType gmsh_celltype_to_oiseau_celltype(const std::size_t s) {
  switch (s) {
  case 15:
    return oiseau::mesh::get_cell_type("point");
  case 1:
    return oiseau::mesh::get_cell_type("interval");
  case 2:
    return oiseau::mesh::get_cell_type("triangle");
  case 3:
    return oiseau::mesh::get_cell_type("quadrilateral");
  case 4:
    return oiseau::mesh::get_cell_type("tetrahedron");
  case 5:
    return oiseau::mesh::get_cell_type("hexahedron");
  default:
    throw std::runtime_error("Unknown Gmsh cell type: " + std::to_string(s));
  }
}
}  // namespace oiseau::mesh

oiseau::mesh::Mesh oiseau::io::gmsh_read_from_string(const std::string content) {
  std::istringstream stream(content);
  return oiseau::io::gmsh_read_from_stream(stream);
}

oiseau::mesh::Mesh oiseau::io::gmsh_read_from_path(const std::filesystem::path &path) {
  std::ifstream f_handler(path);
  return oiseau::io::gmsh_read_from_stream(f_handler);
}

oiseau::mesh::Mesh oiseau::io::gmsh_read_from_stream(std::istream &f_handler) {
  GMSHFile file = GMSHFile(f_handler);
  std::vector<double> x;
  std::vector<std::vector<std::size_t>> conn;
  std::vector<CellType> cell_types;

  x.reserve(file.nodes_section.num_nodes * 3);
  for (auto &block : file.nodes_section.blocks)
    x.insert(x.end(), block.node_coords.begin(), block.node_coords.end());

  cell_types.reserve(file.elements_section.num_elements);
  conn.reserve(file.elements_section.num_elements);

  for (auto &block : file.elements_section.blocks) {
    std::size_t elem_size = block.data.size() / block.num_elements_in_block;
    for (int i = 0; i < block.num_elements_in_block; ++i) {
      std::vector<std::size_t> tmp;
      tmp.reserve(elem_size - 1);
      for (int j = 1; j < elem_size; ++j) tmp.emplace_back(block.data[i * elem_size + j] - 1);
      cell_types.emplace_back(oiseau::mesh::gmsh_celltype_to_oiseau_celltype(block.element_type));
      conn.emplace_back(std::move(tmp));
    }
  }

  oiseau::mesh::Geometry geometry = oiseau::mesh::Geometry(std::move(x), 3);
  oiseau::mesh::Topology topology = oiseau::mesh::Topology(std::move(conn), std::move(cell_types));
  oiseau::mesh::Mesh mesh(std::move(topology), std::move(geometry));
  return mesh;
};

void oiseau::io::gmsh_write(std::string filename, oiseau::mesh::Mesh &mesh) {};
