#pragma once
#include <memory>
#ifndef EFFECTIVE_BRID_H_
#  define EFFECTIVE_BRID_H_

#  include "Animal.h"
#  include "Nest.h"

namespace effective {
  //> Bird是一个抽象类，因为Fly为纯虚函数。抽象类无法实例化。
  //> 但是一般抽象类都是把析构函数定义为纯虚函数。
  class Bird : public Animal {
  public:
    //> 声明式，防止派生类遮掩了基类的GetDescription(bool hava_weight)函数
    using Animal::GetDescription;
    Bird();
    //> 由于成员变量std::unique_ptr本身不支持拷贝构造函数，
    //> 那么编译器无法为本类生成默认拷贝构造和赋值函数。
    Bird(const Bird& original) = delete;
    Bird& operator=(const Bird& right) = delete;
    Bird(Bird&& original) = default;
    Bird& operator=(Bird&& right) = default;
    //> 在多态下，对象销毁时先调用~Bird()，然后调用~Animal()。
    virtual ~Bird();
    //> 重写的函数需要添加override，这样可以减少错误发生。
    virtual bool Sleep() override;
    //> 子类定义一个与父类同名的重载函数，会遮掩父类函数。
    std::string GetDescription() { return name_; }
    //> 这里定义了纯虚函数，但是依然给出了它的定义。
    //> 此纯虚函数虽然无法在基类对象中调用(纯虚函数所在类属于抽象类，不能创建对象)，
    //> 但是可以使用命名空间调用。
    //> 纯虚函数代表派生类必须重写此函数。提供它的定义的目的是让派生类可以使用
    //> 它相比虚函数的好处是，派生类需要在重写函数的时候决定是否使用基类提供的缺省实现。
    //> 虚函数默认就提供了缺省实现，可以有时候不是派生类需要的。
    //> 可以查看Bird.cc,Sparrow.h/.cc,Woodpecker.h/.cc。
    //> 另外一个做法是不提供纯虚函数的实现，而是独立定义个protect级别的函数，
    //> 函数内封装实现，供派生类使用。
    virtual void Fly() = 0;

  private:
    std::string feather_color_;
    //> 这里定义int数组指针的目的是为了展示一下在构造函数和析构函数中，内存的new和delete。
    //> 其实使用list更合适。
    //> 因为list不需要显示在构造和析构中声明，在list从栈中销毁的时候，
    //> 会自动调用元素的析构函数进行销毁。
    int* location_;
    // TODO:现代C++已经不推荐使用裸指针了，应该考虑用智能指针
    // Nest* nest_ptr_;
    std::unique_ptr<Nest> nest_ptr_;
  };
}  // namespace effective
#endif  // EFFECTIVE_BRID_H_
