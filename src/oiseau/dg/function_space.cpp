#include "oiseau/dg/function_space.hpp"

#include <cstddef>
#include <memory>
#include <span>
#include <vector>

#include "oiseau/dg/nodal/element.hpp"

namespace oiseau::dg {

FunctionSpace::FunctionSpace(const std::shared_ptr<const mesh::Mesh>& mesh,
                             const std::vector<nodal::Element>& elements,
                             const std::vector<std::size_t>& orders)
    : m_mesh(mesh), m_elements(elements), m_orders(orders) {}
std::span<const nodal::Element> FunctionSpace::elements() const { return {m_elements}; }
std::span<const std::size_t> FunctionSpace::orders() const { return {m_orders}; }

}  // namespace oiseau::dg
