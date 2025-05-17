#pragma once
#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefTetrahedron : public RefElement {
 public:
  explicit RefTetrahedron(unsigned order);
};
}  // namespace oiseau::dg::nodal
