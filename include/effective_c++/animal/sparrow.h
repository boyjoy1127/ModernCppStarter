#pragma once
#ifndef EFFECTIVE_SPARROW_H_
#  define EFFECTIVE_SPARROW_H_

#  include "bird.h"

namespace effective {
  //> 虚继承，承诺给派生类共享自己的虚基类。用于应对多重继承下，多个基类冲突的情况。
  //> vitual继承会增加大小、速度、初始化复杂度等等成本。如果virtual base
  //> classes不带任何数据，将是最具实用价值的情况。
  class Sparrow : virtual public Bird {
  public:
    Sparrow() = default;
    Sparrow(const Sparrow& original) = delete;
    Sparrow& operator=(const Sparrow& right) = delete;
    Sparrow(Sparrow&& original) = default;
    Sparrow& operator=(Sparrow&& right) = default;
    //> 在多态下，对象销毁时先调用~Sparrow()，然后调用~Bird()。
    virtual ~Sparrow() = default;
    virtual void Fly();
  };
}  // namespace effective
#endif  // EFFECTIVE_SPARROW_H_