#pragma once
#ifndef EFFECTIVE_LAMBDA_H_
#  define EFFECTIVE_LAMBDA_H_

#  include <string>
// 使用C++14语法演示
// lambda语法最主要的地方在捕获和形参列表。
// 捕获语法，有如下，但是只推荐使用部分方式。
// []：默认不捕获任何变量；推荐！！
// [=]：默认以值捕获所有变量；
// [&]：默认以引用捕获所有变量；
// [x]：仅以值捕获x，其它变量不捕获；推荐！！
// [&x]：仅以引用捕获x，其它变量不捕获；推荐！！
// [=, &x]：默认以值捕获所有变量，但是x是例外，通过引用捕获；
// [&, x]：默认以引用捕获所有变量，但是x是例外，通过值捕获；
// [this]：通过引用捕获当前对象（其实是复制指针）；推荐！！
// [*this]：通过传值方式捕获当前对象；推荐！！
//
// 形参列表
// 常规的形参列表跟函数的形参列表没有区别，按需使用就可以。
// 当遇到模板函数时，则需要考虑使用auto和auto&&。分别对应T和T&&
namespace effective {  // 过滤函数
  class Widget {
  public:
    std::string Lambda1() const;  // 向filters添加条目
    std::string Lambda2() const;  // 向filters添加条目
    std::string Lambda3() const {
      // 支持模板+完美转发
      auto filter
          = [](auto&&... param) { return Normalize(std::forward<decltype(param)>(param)...); };
      if (filter(0)) {
        return "true";
      }
      return "false";
    }
    std::string Lambda4() const {
      // 支持模板
      auto filter = [](auto param) { return Normalize(param); };
      if (filter(0)) {
        return "true";
      }
      return "false";
    }
    static bool Normalize(const int& x) {
      if (x > 0) {
        return true;
      }
      return false;
    }
    // 这里右值引用的情况下，产生相反的结果。
    static bool Normalize(int&& x) {
      if (x > 0) {
        return false;
      }
      return true;
    }

  private:
    int divisor_{2};  // 在Widget的过滤器使用
  };

}  // namespace effective
#endif  // EFFECTIVE_LAMBDA_H_