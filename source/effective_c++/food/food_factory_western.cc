#include "effective_c++/food/food_factory_western.h"

#include <vector>

#include "effective_c++/food/food.h"
#include "effective_c++/food/food_factory.h"
using effective::Food;

std::vector<Food> effective::western::ProduceWesternFood() {
  auto factory = FoodFactory::GetInstance();
  auto cheeses = factory.ProduceCheese();
  auto sausages = factory.ProduceSausage();
  auto hams = factory.ProduceHam();
  std::vector<Food> result = {cheeses, sausages, hams};
  return result;
}