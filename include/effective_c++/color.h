#pragma once
#ifndef EFFECTIVE_COLOR_H_
#  define EFFECTIVE_COLOR_H_
#  include <string>
namespace effective {
  //> Effective C++ 18
  //> 我们需要自定义类型作为draw的输入参数，为什么没有使用emun是因为它安全性不好，
  //> 它可以被隐式转换成int使用，Color类则私有化了Color(int)函数。
  class Color {
  public:
    static Color Red() { return Color("Red"); }
    static Color Blue() { return Color("Blue"); }
    static Color Brown() { return Color("Brown"); }
    static Color Green() { return Color("Green"); }
    std::string color_name() { return color_name_; }

  private:
    explicit Color(std::string color);
    std::string color_name_;
  };
}  // namespace effective
#endif  // EFFECTIVE_COLOR_H_