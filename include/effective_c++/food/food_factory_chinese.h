#pragma once
#ifndef EFFECTIVE_FOOD_FACTORY_CHINESE_H_
#  define EFFECTIVE_FOOD_FACTORY_CHINESE_H_
#  include "effective_c++/food/food.h"
//> Effective C++ 23，使用non-member,non-friend函数展示封装性
namespace effective {
  namespace chinese {
    std::vector<Food> ProduceChineseFood();
  }
}  // namespace effective
#endif  // EFFECTIVE_FOOD_FACTORY_CHINESE_H_