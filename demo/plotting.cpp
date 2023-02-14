#include "oiseau/dg/nodal/utils.hpp"
#include "oiseau/plotting/pyplot.hpp"

using namespace oiseau::dg::nodal::utils;

int main() {
  plt::scoped_interpreter guard{};
  auto tri = generate_triangle_equidistant_nodes(3);
  xt::xarray<double> x = xt::col(tri, 0);
  xt::xarray<double> y = xt::col(tri, 1);
  auto [fig, ax] = plt::subplots("layout"_a = "constrained");
  ax.scatter(x, y);
  fmt::print("x = {}\n", x);
  fmt::print("y = {}\n", y);
  plt::show();
  return 0;
}
