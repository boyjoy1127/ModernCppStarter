#include "doctest/doctest.h"
#include "effective_c++/stl/hello_stl.h"

TEST_CASE("Test") {
  using namespace effective;
  auto test = new Test();
  CHECK(test->show<int>(5) == 5);
}
