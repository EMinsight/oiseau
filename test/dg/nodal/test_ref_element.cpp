#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

#include "oiseau/dg/nodal/ref_element.hpp"
#include "oiseau/dg/nodal/ref_line.hpp"
#include "oiseau/test_macros.hpp"

using oiseau::dg::nodal::RefElement;
using oiseau::dg::nodal::RefLine;
using std::unique_ptr;

TEST(test_ref_element, invalid_order) {
  EXPECT_THROW({ std::make_unique<RefLine>(0); }, std::invalid_argument);
}
