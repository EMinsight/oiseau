#include "oiseau/dg/nodal/ref_hexahedron.hpp"

#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/core/xshape.hpp>
#include <xtensor/core/xtensor_forward.hpp>
#include <xtensor/generators/xbuilder.hpp>
#include <xtensor/misc/xmanipulation.hpp>
#include <xtensor/views/xslice.hpp>
#include <xtensor/views/xview.hpp>

#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/dg/nodal/utils.hpp"

namespace oiseau::dg::nodal {

using utils::d_matrix_3d;
using utils::grad_vandermonde_3d_tensor;
using utils::vandermonde_3d_tensor;

RefHexahedron::RefHexahedron(unsigned order) : RefElement(order) {
  this->m_np = (order + 1) * (order + 1) * (order + 1);
  this->m_nfp = (order + 1) * (order + 1);
  this->m_r = detail::generate_hexahedron_nodes(this->m_order);
  this->m_v = vandermonde_3d_tensor(this->m_order, this->m_r);
  this->m_gv = grad_vandermonde_3d_tensor(this->m_order, this->m_r);
  this->m_d = d_matrix_3d(this->m_v, this->m_gv);
}

}  // namespace oiseau::dg::nodal

namespace oiseau::dg::nodal::detail {
xt::xarray<double> generate_hexahedron_nodes(unsigned order) {
  xt::xarray<double> r1d = utils::jacobi_gl(order, 0.0, 0.0);
  auto [R, S, T] = xt::meshgrid(r1d, r1d, r1d);
  return xt::stack(xt::xtuple(xt::flatten(R), xt::flatten(S), xt::flatten(T)), 1);
}

}  // namespace oiseau::dg::nodal::detail
