#pragma once
#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefQuadrilateral : public RefElement {
 public:
  explicit RefQuadrilateral(unsigned order);
};
}  // namespace oiseau::dg::nodal
