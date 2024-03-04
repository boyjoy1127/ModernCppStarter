#pragma once
#ifndef EFFECTIVE_HAM_H_
#  define EFFECTIVE_HAM_H_
#  include "effective_c++/food/food.h"
namespace effective {
  class Ham final : public Food {
  public:
    //>
    // 使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
    //> 这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他
    //> 默认成员函数不再生成，造成错误。
    Ham() = default;
    Ham(const Ham& original) = default;
    Ham& operator=(const Ham& right) = default;
    Ham(Ham&& original) = default;
    Ham& operator=(Ham&& right) = default;

    /**
     * @brief This is a deconstructor function.
     */
    virtual ~Ham() = default;
  };
}  // namespace effective
#endif  // EFFECTIVE_HAM_H_