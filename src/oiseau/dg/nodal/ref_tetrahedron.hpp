#pragma once
#include "oiseau/dg/nodal/ref_elements.hpp"

namespace oiseau::dg::nodal {

class RefTetrahedron : public RefElement {
 public:
  explicit RefTetrahedron(unsigned order);
};
}  // namespace oiseau::dg::nodal
