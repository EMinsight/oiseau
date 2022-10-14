#include <pybind11/pybind11.h>
#include "oiseau/mesh/cell.hpp"

namespace py = pybind11;

namespace oiseau::wrappers {
void mesh(py::module &m) {
  py::class_<mesh::Cell, std::unique_ptr<mesh::Cell, py::nodelete>> cell(m, "Cell");
  cell.def("facet", &mesh::Cell::facet);
  cell.def("name", &mesh::Cell::name);
  m.def("get_cell_type", &mesh::get_cell_type);
}

}  // namespace oiseau::wrappers
