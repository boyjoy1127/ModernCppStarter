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
    virtual std::string tick() const;
    virtual void stop();

  private:
    virtual std::string onTick() const;
    int tick_frequency;
    bool is_running{true};
  };
}  // namespace effective
#endif  // EFFECTIVE_CLOCK_H_