#include "oiseau/mesh/mesh.hpp"

using namespace oiseau::mesh;

Topology& Mesh::topology() { return _topology; }
const Topology& Mesh::topology() const { return _topology; }
Geometry& Mesh::geometry() { return _geometry; }
const Geometry& Mesh::geometry() const { return _geometry; }
Mesh::~Mesh() {}
