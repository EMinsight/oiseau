#include "oiseau/dg/nodal/element.hpp"

#include <memory>
#include <utility>

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

Element::Element(unsigned order, std::shared_ptr<RefElement> ref_elem)
    : m_order(order), m_reference(std::move(ref_elem)) {}
const RefElement& Element::reference() const { return *m_reference; }
unsigned Element::order() const { return m_order; }
}  // namespace oiseau::dg::nodal
