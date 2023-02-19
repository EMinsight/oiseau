#pragma once

namespace oiseau::mesh {
class Mesh;
}

namespace oiseau::dg {

class FunctionSpace {
 public:
  FunctionSpace(const FunctionSpace& V) = delete;
  FunctionSpace(FunctionSpace&& V) = default;
  virtual ~FunctionSpace() = default;
  FunctionSpace& operator=(const FunctionSpace& V) = delete;
  FunctionSpace& operator=(FunctionSpace&& V) = default;

 private:
  std::shared_ptr<const mesh::Mesh> m_mesh;
  // std::shared_ptr<const mesh::Mesh> m_element; TODO: this might be a vector
};

}  // namespace oiseau::dg
