#pragma once

#include <filesystem>

#include "oiseau/mesh/mesh.hpp"

namespace oiseau::io {
oiseau::mesh::Mesh gmsh_read_from_path(const std::filesystem::path& path);
oiseau::mesh::Mesh gmsh_read_from_string(const std::string&);
oiseau::mesh::Mesh gmsh_read_from_stream(std::istream& f_handler);
void gmsh_write(const std::string& filename, const oiseau::mesh::Mesh& mesh);
}  // namespace oiseau::io
