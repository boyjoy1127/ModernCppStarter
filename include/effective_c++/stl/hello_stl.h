#pragma once
#ifndef EFFECTIVE_HELLO_STL_H_
#  define EFFECTIVE_HELLO_STL_H_
#  include <iostream>

namespace effective {
  class Test {
  public:
    template <typename T> T show(T t) { return t; }
  };
}  // namespace effective
#endif  // EFFECTIVE_HELLO_STL_H_