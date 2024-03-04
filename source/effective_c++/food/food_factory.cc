#include "effective_c++/food/food_factory.h"

#include "effective_c++/food/cheese.h"
#include "effective_c++/food/food.h"
#include "effective_c++/food/ham.h"
#include "effective_c++/food/sausage.h"
#include "effective_c++/food/soyabean_milk.h"
#include "effective_c++/food/twisted_cruller.h"
using std::string;
using namespace effective;

FoodFactory& FoodFactory::GetInstance() {
  static FoodFactory result;
  return result;
}

Food FoodFactory::ProduceCheese() { return Cheese(); }
Food FoodFactory::ProduceSausage() { return Sausage(); }
Food FoodFactory::ProduceHam() { return Ham(); }
Food FoodFactory::ProduceSoyaBeanMilk() { return SoyaBeanMilk(); }
Food FoodFactory::ProduceTwistedCruller() { return TwistedCruller(); }
