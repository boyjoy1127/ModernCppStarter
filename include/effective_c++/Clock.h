#pragma once
#ifndef EFFECTIVE_CLOCK_H_
#  define EFFECTIVE_CLOCK_H_
#  include <string>

namespace effective {
  /**
   * @brief Clock是一个实例类，没有真正实现它的功能。
   * @details Clock是一个定时器，内部会按照tickFrequency频率调用onTick()
   */
  class Clock {
  public:
    Clock() = default;
    explicit Clock(int tickFrequency);
    virtual std::string Tick() const;
    virtual void Stop();

  private:
    virtual std::string OnTick() const;
    //> 成员变量初始化的顺序为：先声明时初始化，然后初始化列表初始化，最后构造函数初始化。
    //> 如果调用了一个类的默认构造函数，那么这个变量的值则来自于声明初始化。如果声明时
    //> 未初始化，则此变量值为该类型的默认值。
    int tick_frequency_{1};
    bool is_running_{true};
  };
}  // namespace effective
#endif  // EFFECTIVE_CLOCK_H_