#pragma once

#ifndef EFFECTIVE_SPARROWPECKER_H_
#  define EFFECTIVE_SPARROWPECKER_H_
#  include "sparrow.h"
#  include "wood_pecker.h"

namespace effective {
  // 多重继承之菱形继承，Sparrow和Woodpecker分别虚拟继承了Bird。
  class SparrowPecker : public Sparrow, public Woodpecker {
  public:
    SparrowPecker();
    SparrowPecker(const SparrowPecker& original) = delete;
    SparrowPecker& operator=(const SparrowPecker& right) = delete;
    SparrowPecker(SparrowPecker&& original) = delete;
    SparrowPecker& operator=(SparrowPecker&& right) = delete;
    //> 在多态下，对象销毁时先调用~SparrowPecker()，然后调用~Bird()。
    ~SparrowPecker();
    //> 多重继承下，由于Sparrow和Woodpecker继承的基类的Fly为纯虚函数。
    //> 所以基类并没有提供Fly函数出来，也就是Sparrow和Woodpecker无法共享虚基类的Fly,
    //> 这使得SparrowPecker继承了两个Fly分别来自Sparrow和Woodpecker。
    //> 所以SparrowPecker应该自己重写一个Fly(),这样可以遮掩继承而来Fly。
    //> 遮掩原理参考EffectiveC++ Item32。
    virtual void Fly();
  };
}  // namespace effective
#endif  // EFFECTIVE_SPARROWPECKER_H_