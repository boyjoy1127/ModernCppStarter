#pragma once
#ifndef EFFECTIVE_NEST_H_
#  define EFFECTIVE_NEST_H_
#  include "Home.h"
#  include "Lock.h"
namespace effective {
  /**
   * @brief The Nest class provide address for animal living
   * @details The Nest class should not be derived
   */
  class Nest final : public Home {
  public:
    Nest() = default;
    Nest(const Nest& original) = default;
    Nest& operator=(const Nest& right) = default;
    Nest(Nest&& original) = delete;
    Nest& operator=(Nest&& right) = delete;
    virtual ~Nest() = default;

  private:
    virtual int doHealthValue() const override;
    virtual void doDraw(int color) const override;
    virtual void onTick() const override;

    Lock key;  // This key is used by bird, only one bird could stay in the nest at one time.
  };
}  // namespace effective
#endif  // EFFECTIVE_NEST_H_