#pragma once

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {
class RefTriangle : public RefElement {
 public:
  explicit RefTriangle(unsigned order);
};
}  // namespace oiseau::dg::nodal
