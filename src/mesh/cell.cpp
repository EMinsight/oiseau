#include "oiseau/mesh/cell.h"


static std::unordered_map<oiseau::mesh::CellType, std::string> CELLTYPE_TO_STRING = {
    {oiseau::mesh::CellType::point, "point"},
    {oiseau::mesh::CellType::line, "line"},
    {oiseau::mesh::CellType::triangle, "triangle"},
    {oiseau::mesh::CellType::tetrahedron, "tetrahedron"},
};

static std::unordered_map<std::string, oiseau::mesh::CellType> CELLTYPE_FROM_STRING = reverse_map(CELLTYPE_TO_STRING);

oiseau::mesh::CellType & oiseau::mesh::celltype_from_string(std::string &name){
  return CELLTYPE_FROM_STRING[name];
}
std::string  &oiseau::mesh::celltype_to_string(CellType &type){
  return CELLTYPE_TO_STRING[type];
}
