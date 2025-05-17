#pragma once

#include "oiseau/dg/nodal/ref_elements.hpp"

namespace oiseau::dg::nodal {

class RefLine : public RefElement {
 public:
  explicit RefLine(unsigned order);
};
}  // namespace oiseau::dg::nodal
