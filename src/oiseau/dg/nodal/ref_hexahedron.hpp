#pragma once

#include <xtensor/core/xtensor_forward.hpp>

#include "oiseau/dg/nodal/ref_element.hpp"

namespace oiseau::dg::nodal {

class RefHexahedron : public RefElement {
 public:
  explicit RefHexahedron(unsigned order);
};

namespace detail {

xt::xarray<double> generate_hexahedron_nodes(unsigned order);

}
}  // namespace oiseau::dg::nodal
