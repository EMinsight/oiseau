#pragma once

#include "oiseau/mesh/mesh.hpp"

namespace oiseau::io {
oiseau::mesh::Mesh gmsh_read(std::string filename);
void gmsh_write(std::string filename, oiseau::mesh::Mesh &mesh);
}  // namespace oiseau::io
