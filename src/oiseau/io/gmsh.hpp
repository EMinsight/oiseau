#pragma once

#include <cstddef>
#include <filesystem>
#include <istream>
#include <string>

#include "oiseau/mesh/cell.hpp"
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::io::detail {
oiseau::mesh::CellType gmsh_celltype_to_oiseau_celltype(const std::size_t s);
}

namespace oiseau::io {
oiseau::mesh::Mesh gmsh_read_from_path(const std::filesystem::path& path);
oiseau::mesh::Mesh gmsh_read_from_string(const std::string&);
oiseau::mesh::Mesh gmsh_read_from_stream(std::istream& f_handler);
void gmsh_write(const std::string& filename, const oiseau::mesh::Mesh& mesh);
}  // namespace oiseau::io
