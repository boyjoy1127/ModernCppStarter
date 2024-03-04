#include "doctest/doctest.h"
#include "effective_c++/animal/sparrow.h"

TEST_CASE("Sparrow") {
  using namespace effective;
  auto one_bird = Sparrow();
  CHECK(one_bird.GetDescription() == "");
}
