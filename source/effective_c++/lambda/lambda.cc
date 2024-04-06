#include "effective_c++/lambda/lambda.h"

#include <string>
#include <utility>

using std::string;
using namespace effective;

string Widget::Lambda1() const {
  // 要复制进闭包的对象
  // C++14：
  auto filter = [divisor = divisor_](int value) { return value % divisor == 0; };
  if (filter(0)) {
    return "true";
  }
  return "false";
}

string Widget::Lambda2() const {
  // 要移动进闭包的对象
  auto filter = [divisor = std::move(divisor_)](int value) { return value % divisor == 0; };
  if (filter(0)) {
    return "true";
  }
  return "false";
}
