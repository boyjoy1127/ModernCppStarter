#include "effective_c++/home/cave.h"

#include "doctest/doctest.h"

TEST_CASE("Cave") {
  using namespace effective;
  auto one_cave = Cave("ParaMountain");
  CHECK(one_cave.draw(3) == "let paint the house as Brown");
  CHECK(one_cave.healthValue() == "before check health of full Cave after.");
  CHECK(one_cave.GetAddress("decorate ") == "decorate ParaMountain");
  CHECK(one_cave.GetAddress() == "ParaMountain");
  CHECK(one_cave.boardcastAddress() == "This from home begin send address Tick begin My cave address is : ParaMountainMy cave address is : ParaMountainMy cave address is : ParaMountainend.");
}
