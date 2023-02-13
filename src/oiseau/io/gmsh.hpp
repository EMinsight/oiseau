#pragma once

#include <string_view>
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::io {
oiseau::mesh::Mesh gmsh_read(std::string filename);
void gmsh_write(const std::string_view filename, oiseau::mesh::Mesh &mesh);
}  // namespace oiseau::io
