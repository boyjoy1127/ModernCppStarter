#pragma once
#ifndef EFFECTIVE_WOODPECKER_H_
#  define EFFECTIVE_WOODPECKER_H_

#  include "bird.h"

namespace effective {
  //> 虚继承，承诺给派生类共享自己的虚基类。用于应对多重继承下，多个基类冲突的情况。
  //> vitual继承会增加大小、速度、初始化复杂度等等成本。如果virtual base
  //> classes不带任何数据，将是最具实用价值的情况。
  class Woodpecker : virtual public Bird {
  public:
    Woodpecker() = default;
    Woodpecker(const Woodpecker& original) = delete;
    Woodpecker& operator=(const Woodpecker& right) = delete;
    Woodpecker(Woodpecker&& original) = default;
    Woodpecker& operator=(Woodpecker&& right) = default;
    //> 在多态下，对象销毁时先调用~Woodpecker()，然后调用~Bird()。
    virtual ~Woodpecker() = default;
    virtual void Fly();
  };
}  // namespace effective
#endif  // EFFECTIVE_WOODPECKER_H_