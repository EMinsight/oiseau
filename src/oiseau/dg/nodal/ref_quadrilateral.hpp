#pragma once
#include "oiseau/dg/nodal/ref_elements.hpp"

namespace oiseau::dg::nodal {

class RefQuadrilateral : public RefElement {
 public:
  explicit RefQuadrilateral(unsigned order);
};
}  // namespace oiseau::dg::nodal
