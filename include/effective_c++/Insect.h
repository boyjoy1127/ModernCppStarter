#pragma once
#ifndef EFFECTIVE_INSECT_H_
#  define EFFECTIVE_INSECT_H_

#  include "animal.h"

namespace effective {
  //> Insect是一个抽象类，因为Fly为纯虚函数。抽象类无法实例化。
  //> 但是一般抽象类都是把析构函数定义为纯虚函数。
  class Insect : public Animal {
  public:
    Insect() = default;
    Insect(const Insect& original) = default;
    Insect& operator=(const Insect& right) = default;
    Insect(Insect&& original) = default;
    Insect& operator=(Insect&& right) = default;
    //> 在多态下，对象销毁时先调用~Insect()，然后调用~Animal()。
    virtual ~Insect() = default;
    virtual bool Sleep();
  };
}  // namespace effective
#endif  // EFFECTIVE_INSECT_H_
