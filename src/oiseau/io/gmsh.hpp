#pragma once

#include <string_view>
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::io {
void gmsh_read(const std::string_view filename, oiseau::mesh::Mesh &mesh);
void gmsh_write(const std::string_view filename, oiseau::mesh::Mesh &mesh);
}  // namespace oiseau::io
