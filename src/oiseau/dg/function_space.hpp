#pragma once

#include <iostream>
#include <span>
#include <vector>

#include "oiseau/dg/nodal/element.hpp"
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::dg {

class FunctionSpace {
 public:
  FunctionSpace(const FunctionSpace& V) = delete;
  FunctionSpace(const mesh::Mesh& mesh, const std::vector<unsigned>& orders);
  FunctionSpace(FunctionSpace&& V) = default;
  virtual ~FunctionSpace() = default;
  FunctionSpace& operator=(const FunctionSpace& V) = delete;
  FunctionSpace& operator=(FunctionSpace&& V) = delete;

  inline const mesh::Mesh& mesh() const { return m_mesh; };
  std::span<const nodal::Element> elements() const;
  std::span<const unsigned> orders() const;

 private:
  const mesh::Mesh& m_mesh;
  std::vector<nodal::Element> m_elements;
  const std::vector<unsigned> m_orders;
};

}  // namespace oiseau::dg
