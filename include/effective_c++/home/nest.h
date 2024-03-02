#pragma once
#ifndef EFFECTIVE_NEST_H_
#  define EFFECTIVE_NEST_H_
#  include "effective_c++/home/home.h"
#  include "effective_c++/lock.h"
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

    /**
     * @brief Construct the Nest object with address.
     * @param name The address of the Home.
     */
    explicit Nest(std::string address);

  private:
    virtual std::string doHealthValue() const override;
    virtual std::string doDraw(int color) const override;
    virtual std::string onTick() const override;

    Lock key;  // This key is used by bird, only one bird could stay in the nest at one time.
  };
}  // namespace effective
#endif  // EFFECTIVE_NEST_H_