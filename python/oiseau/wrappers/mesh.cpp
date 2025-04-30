#include <pybind11/pybind11.h>
#include "oiseau/mesh/cell.hpp"

namespace py = pybind11;

namespace oiseau::wrappers {
void mesh(py::module &m) {
  py::class_<mesh::Cell, std::unique_ptr<mesh::Cell, py::nodelete>> cell(m, "Cell");
  cell.def("facet", &mesh::Cell::facet);
  cell.def("name", &mesh::Cell::name);
  cell.def(
      "get_entity_vertices",
      [](mesh::Cell &self, int dim) {
        std::vector<std::vector<int>> cpp_result = self.get_entity_vertices(dim);
        return py::array(py::cast(cpp_result));
      },
      py::arg("dim"), "Get entity vertices.");
  m.def("get_cell_type", &mesh::get_cell_type);
}

}  // namespace oiseau::wrappers
