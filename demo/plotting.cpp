#include "oiseau/dg/nodal/utils.hpp"
#include "oiseau/plotting/pyplot.hpp"

using namespace oiseau::dg::nodal::utils;

int main() {
  plt::scoped_interpreter guard{};
  xt::xarray<double> tri = generate_triangle_equidistant_nodes(3);
  auto x = xt::col(tri, 0);
  auto y = xt::col(tri, 1);
  auto z = xt::col(tri, 0);

  plt::Figure fig = plt::figure();
  auto ax = fig.add_subplot("projection"_a = "3d");

  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << z << std::endl;

  ax.scatter(x, y, z);
  plt::show();
  return 0;
}
