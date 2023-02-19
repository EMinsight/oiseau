#include "oiseau/dg/nodal/utils.hpp"
#include "oiseau/plotting/pyplot.hpp"

using namespace oiseau::dg::nodal::utils;

int main() {
  plt::scoped_interpreter guard{};
  auto tri = generate_triangle_equidistant_nodes(3);
  xt::xarray<double> x = xt::col(tri, 0);
  xt::xarray<double> y = xt::col(tri, 1);
  xt::xarray<double> z = xt::col(tri, 0);
  auto fig = plt::figure();
  auto ax = fig.add_subplot("projection"_a = "3d");
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << z << std::endl;
  ax.scatter(x, y, z);
  plt::show();
  return 0;
}
