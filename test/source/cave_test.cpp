#include "effective_c++/home/cave.h"

#include "doctest/doctest.h"
#include "effective_c++/color.h"

TEST_CASE("Cave") {
  using namespace effective;
  auto one_cave = Cave("ParaMountain");
  CHECK(one_cave.Draw(Color::Brown()) == "let paint the cave as Brown");
  CHECK(one_cave.HealthValue() == "before check health of full Cave after.");
  CHECK(one_cave.GetAddress("decorate ") == "decorate ParaMountain");
  CHECK(one_cave.GetAddress() == "ParaMountain");
  CHECK(one_cave.BoardcastAddress() == "This from home begin send address Tick begin My cave address is : ParaMountainMy cave address is : ParaMountainMy cave address is : ParaMountainend.");
}
