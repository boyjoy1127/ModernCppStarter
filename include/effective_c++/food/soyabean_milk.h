#pragma once
#ifndef EFFECTIVE_SOYABEANMILK_H_
#  define EFFECTIVE_SOYABEANMILK_H_
#  include "effective_c++/food/food.h"
namespace effective {
  class SoyaBeanMilk final : public Food {
  public:
    //>
    // 使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
    //> 这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他
    //> 默认成员函数不再生成，造成错误。
    SoyaBeanMilk() = default;
    SoyaBeanMilk(const SoyaBeanMilk& original) = default;
    SoyaBeanMilk& operator=(const SoyaBeanMilk& right) = default;
    SoyaBeanMilk(SoyaBeanMilk&& original) = default;
    SoyaBeanMilk& operator=(SoyaBeanMilk&& right) = default;

    /**
     * @brief This is a deconstructor function.
     */
    virtual ~SoyaBeanMilk() = default;
  };
}  // namespace effective
#endif  // EFFECTIVE_SOYABEANMILK_H_