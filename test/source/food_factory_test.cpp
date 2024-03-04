#include <vector>

#include "doctest/doctest.h"
#include "effective_c++/food/food_factory_chinese.h"
#include "effective_c++/food/food_factory_western.h"

TEST_CASE("FoodFactory") {
  using effective::chinese::ProduceChineseFood;
  using effective::western::ProduceWesternFood;
  CHECK(ProduceWesternFood().size() == 3);
  CHECK(ProduceChineseFood().size() == 2);
}
