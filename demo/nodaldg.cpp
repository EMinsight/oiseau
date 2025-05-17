#include <iostream>
#include <xtensor/containers/xadapt.hpp>
#include <xtensor/io/xio.hpp>

#include "oiseau/dg/nodal/ref_line.hpp"

using namespace oiseau::dg::nodal;

int main() {
  auto elem = RefLine(3);
  std::cout << elem.v() << std::endl;
  std::cout << elem.gv() << std::endl;
  std::cout << elem.d() << std::endl;
  auto shape = elem.r().shape();
  std::cout << xt::adapt(shape) << std::endl;
  return 0;
}
