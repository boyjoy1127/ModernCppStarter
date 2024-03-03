#include "effective_c++/home/home_factory.h"

#include "doctest/doctest.h"
#include "effective_c++/color.h"

TEST_CASE("HomeFactory") {
  using namespace effective;
  auto home_factory = HomeFactory();

  auto one_cave = home_factory.MakeHome("Cave");
  CHECK(one_cave->Draw(Color::Brown()) == "let paint the cave as Brown");
  CHECK(one_cave->HealthValue() == "before check health of full Cave after.");
  CHECK(one_cave->GetAddress("decorate ") == "decorate ParaMountain");
  CHECK(one_cave->GetAddress() == "ParaMountain");
  CHECK(one_cave->BoardcastAddress() == "This from home begin send address Tick begin My cave address is : ParaMountainMy cave address is : ParaMountainMy cave address is : ParaMountainend.");

  auto one_nest = home_factory.MakeHome("Nest");
  CHECK(one_nest->Draw(Color::Blue()) == "let paint the nest as Blue");
  CHECK(one_nest->HealthValue() == "before check health of full Nest after.");
  CHECK(one_nest->GetAddress("decorate ") == "decorate ParaNest");
  CHECK(one_nest->BoardcastAddress() == "This from home begin send address Tick begin My nest address is : ParaNestMy nest address is : ParaNestMy nest address is : ParaNestend.");

  CHECK(home_factory.GetCacheSize() == 0);
  home_factory.GetHome("Cave");
  home_factory.GetHome("Nest");
  home_factory.GetHome("Cave");
  home_factory.GetHome("Nest");
  CHECK(home_factory.GetCacheSize() == 2);
}
