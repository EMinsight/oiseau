#pragma once

#include "oiseau/dg/nodal/ref_elements.hpp"

namespace oiseau::dg::nodal {

class RefHexahedron : public RefElement {
 public:
  explicit RefHexahedron(unsigned order);
};
}  // namespace oiseau::dg::nodal
