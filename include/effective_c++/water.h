#pragma once
#ifndef EFFECTIVE_WATER_H_
#  define EFFECTIVE_WATER_H_
#  include <memory>
namespace effective {
  //> ModernEffectiveC++_22item
  class Water final {
  public:
    Water();
    ~Water();
    Water(Water&& rhs);
    Water& operator=(Water&& rhs);
    Water(const Water& rhs);
    Water& operator=(const Water& rhs);

  private:
    //> Water类的实现细节放置在该前向声明的实现类中。
    struct Impl;
    //> 指向实现类Impl的私有指针
    std::unique_ptr<Impl> pimpl_;
  };
}  // namespace effective
#endif  // EFFECTIVE_WATER_H_