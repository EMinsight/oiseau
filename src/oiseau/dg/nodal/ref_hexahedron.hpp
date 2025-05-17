#pragma once

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefHexahedron : public RefElement {
 public:
  explicit RefHexahedron(unsigned order);
};
}  // namespace oiseau::dg::nodal
