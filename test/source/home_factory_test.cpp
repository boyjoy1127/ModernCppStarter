#include "effective_c++/home/home_factory.h"

#include "doctest/doctest.h"

TEST_CASE("HomeFactory") {
  using namespace effective;
  auto home_factory = HomeFactory();

  auto one_cave = home_factory.makeHome("Cave");
  CHECK(one_cave->draw(3) == "let paint the house as Brown");
  CHECK(one_cave->healthValue() == "before check health of full Cave after.");
  CHECK(one_cave->GetAddress("decorate ") == "decorate ParaMountain");
  CHECK(one_cave->GetAddress() == "ParaMountain");
  CHECK(one_cave->boardcastAddress() == "This from home begin send address Tick begin My cave address is : ParaMountainMy cave address is : ParaMountainMy cave address is : ParaMountainend.");

  auto one_nest = home_factory.makeHome("Nest");
  CHECK(one_nest->draw(2) == "let paint the house as Blue");
  CHECK(one_nest->healthValue() == "before check health of full Nest after.");
  CHECK(one_nest->GetAddress("decorate ") == "decorate ParaNest");
  CHECK(one_nest->boardcastAddress() == "This from home begin send address Tick begin My nest address is : ParaNestMy nest address is : ParaNestMy nest address is : ParaNestend.");

  CHECK(home_factory.getCacheSize() == 0);
  home_factory.getHome("Cave");
  home_factory.getHome("Nest");
  home_factory.getHome("Cave");
  home_factory.getHome("Nest");
  CHECK(home_factory.getCacheSize() == 2);
}
