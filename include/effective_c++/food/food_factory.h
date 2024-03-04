#pragma once
#ifndef EFFECTIVE_FOOD_FACTORY_H_
#  define EFFECTIVE_FOOD_FACTORY_H_

#  include "effective_c++/food/food.h"
//> Effective C++ 23
namespace effective {
  class FoodFactory {
  public:
    Food ProduceCheese();
    Food ProduceSausage();
    Food ProduceHam();
    Food ProduceSoyaBeanMilk();
    Food ProduceTwistedCruller();
    //> C++ 单例实现手法
    static FoodFactory& GetInstance();
  };
}  // namespace effective
#endif  // EFFECTIVE_FOOD_FACTORY_H_