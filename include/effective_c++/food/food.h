#pragma once
#ifndef EFFECTIVE_FOOD_H_
#  define EFFECTIVE_FOOD_H_
#  include <string>
namespace effective {
  class Food {
  public:
    //> 使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
    //> 这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他
    //> 默认成员函数不再生成，造成错误。
    Food() = default;
    Food(const Food& original) = default;
    Food& operator=(const Food& right) = default;
    Food(Food&& original) = default;
    Food& operator=(Food&& right) = default;

    /**
     * @brief This is a deconstructor function.
     */
    virtual ~Food() = default;

  private:
    std::string name;
  };
}  // namespace effective
#endif  // EFFECTIVE_FOOD_H_