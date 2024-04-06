#include "effective_c++/lambda/lambda.h"

#include "doctest/doctest.h"

TEST_CASE("Widget") {
  using namespace effective;
  auto widget = Widget();
  CHECK(widget.Lambda1() == "true");
  CHECK(widget.Lambda2() == "true");
  CHECK(widget.Lambda3() == "true");
  CHECK(widget.Lambda4() == "false");
}
