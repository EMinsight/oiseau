#pragma once

#include <cstddef>
#include <memory>
#include <span>
#include <vector>

#include "oiseau/dg/nodal/element.hpp"
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::dg {

class FunctionSpace {
 public:
  FunctionSpace(const FunctionSpace& V) = delete;
  FunctionSpace(const std::shared_ptr<const mesh::Mesh>& mesh,
                const std::vector<nodal::Element>& elements,
                const std::vector<std::size_t>& orders);
  FunctionSpace(FunctionSpace&& V) = default;
  virtual ~FunctionSpace() = default;
  FunctionSpace& operator=(const FunctionSpace& V) = delete;
  FunctionSpace& operator=(FunctionSpace&& V) = default;

  std::span<const nodal::Element> elements() const;
  std::span<const std::size_t> orders() const;

 private:
  std::shared_ptr<const mesh::Mesh> m_mesh;
  std::vector<nodal::Element> m_elements;
  std::vector<std::size_t> m_orders;
};

}  // namespace oiseau::dg
