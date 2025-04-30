#include "oiseau/dg/nodal/utils.hpp"
#include "oiseau/plotting/pyplot.hpp"

using namespace oiseau::dg::nodal::utils;

int main() {
  plt::scoped_interpreter guard{};
  xt::xarray<double> tri = generate_triangle_equidistant_nodes(3);

  auto rs = conversion_equilateral_xy_to_rs(tri);
  auto r = xt::col(rs, 0);
  auto s = xt::col(rs, 1);

  {
    auto [fig, ax] = plt::subplots(1, 1, "constrained_layout"_a = true);

    std::cout << "r: " << r << std::endl;
    std::cout << "s: " << s << std::endl;

    ax.scatter(r, s, "label"_a = "scatter");
    ax.set_xlim(-2, 2);
    ax.set_ylim(-2, 2);
    ax.legend();
  }

  auto xyz = generate_tetrahedron_nodes(2);
  auto rst = conversion_equilateral_xyz_to_rst(xyz);

  {
    plt::Figure fig = plt::figure("constrained_layout"_a = true);
    auto ax = fig.add_subplot("projection"_a = "3d");

    auto r = xt::col(rst, 0);
    auto s = xt::col(rst, 1);
    auto t = xt::col(rst, 2);

    ax.scatter(r, s, t);
  }

  plt::show();
  return 0;
}
