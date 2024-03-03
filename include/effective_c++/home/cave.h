#pragma once
#ifndef EFFECTIVE_CAVE_H_
#  define EFFECTIVE_CAVE_H_
#  include "effective_c++/home/home.h"
#  include "effective_c++/lock.h"
namespace effective {
  /**
   * @brief The Cave class provide address for animal living
   * @details The Cave class should not be derived
   */
  class Cave final : public Home {
  public:
    Cave() = default;
    Cave(const Cave& original) = default;
    Cave& operator=(const Cave& right) = default;
    Cave(Cave&& original) = delete;
    Cave& operator=(Cave&& right) = delete;
    virtual ~Cave() = default;

    /**
     * @brief Construct the Cave object with address.
     * @param name The address of the Home.
     */
    explicit Cave(std::string address);

  private:
    virtual std::string DoHealthValue() const override;
    virtual std::string DoDraw(Color color) const override;
    virtual std::string OnTick() const override;
    Lock key;  // This key is used by animal, only one animal could stay in the Cave at one time.
  };
}  // namespace effective
#endif  // EFFECTIVE_CAVE_H_