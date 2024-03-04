#pragma once
#ifndef EFFECTIVE_TWISTEDCRULLER_H_
#  define EFFECTIVE_TWISTEDCRULLER_H_
#  include "effective_c++/food/food.h"
namespace effective {
  class TwistedCruller final : public Food {
  public:
    //> 使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
    //> 这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他
    //> 默认成员函数不再生成，造成错误。
    TwistedCruller() = default;
    TwistedCruller(const TwistedCruller& original) = default;
    TwistedCruller& operator=(const TwistedCruller& right) = default;
    TwistedCruller(TwistedCruller&& original) = default;
    TwistedCruller& operator=(TwistedCruller&& right) = default;

    /**
     * @brief This is a deconstructor function.
     */
    virtual ~TwistedCruller() = default;
  };
}  // namespace effective
#endif  // EFFECTIVE_TWISTEDCRULLER_H_