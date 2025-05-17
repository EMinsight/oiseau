#pragma once

#include <memory>

#include "oiseau/dg/nodal/ref_element.hpp"
namespace oiseau::dg::nodal {

class Element {
 public:
  Element(unsigned order, std::shared_ptr<RefElement> ref_elem);

  const RefElement& reference() const;
  unsigned order() const;

 private:
  unsigned m_order;
  std::shared_ptr<RefElement> m_reference;
};
}  // namespace oiseau::dg::nodal
