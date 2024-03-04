#pragma once
#ifndef EFFECTIVE_FOOD_FACTORY_WESTERN_H_
#  define EFFECTIVE_FOOD_FACTORY_WESTERN_H_
#  include "effective_c++/food/food.h"
//> Effective C++ 23，使用non-member,non-friend函数展示封装性
namespace effective {
  namespace western {
    std::vector<Food> ProduceWesternFood();
  }
}  // namespace effective
#endif  // EFFECTIVE_FOOD_FACTORY_WESTERN_H_