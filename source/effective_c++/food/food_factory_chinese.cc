#include "effective_c++/food/food_factory_chinese.h"

#include <vector>

#include "effective_c++/food/food.h"
#include "effective_c++/food/food_factory.h"

using effective::Food;

std::vector<Food> effective::chinese::ProduceChineseFood() {
  auto factory = FoodFactory::GetInstance();
  auto soya_bean_milk = factory.ProduceSoyaBeanMilk();
  auto twisted_cruller = factory.ProduceTwistedCruller();
  std::vector<Food> result = {soya_bean_milk, twisted_cruller};
  return result;
}