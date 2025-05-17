#pragma once

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefLine : public RefElement {
 public:
  explicit RefLine(unsigned order);
};
}  // namespace oiseau::dg::nodal
