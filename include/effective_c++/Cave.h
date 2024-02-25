#pragma once
#ifndef EFFECTIVE_CAVE_H_
#  define EFFECTIVE_CAVE_H_
#  include "Home.h"
#  include "Lock.h"
namespace effective {
  /**
   * @brief The Cave class provide address for animal living
   * @details The Cave class should not be derived
   */
  class Cave final : private Home {
  public:
    Cave() = default;
    Cave(const Cave& original) = default;
    Cave& operator=(const Cave& right) = default;
    Cave(Cave&& original) = delete;
    Cave& operator=(Cave&& right) = delete;
    virtual ~Cave() = default;

  private:
    virtual int doHealthValue() const override;
    virtual void doDraw(int color) const override;
    virtual void onTick() const override;
    Lock key;  // This key is used by animal, only one animal could stay in the Cave at one time.
  };
}  // namespace effective
#endif  // EFFECTIVE_CAVE_H_