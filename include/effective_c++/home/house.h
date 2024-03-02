#pragma once
#include <memory>
#ifndef EFFECTIVE_HOUSE_H_
#  define EFFECTIVE_HOUSE_H_
#  include <vector>

#  include "effective_c++/home/home.h"
#  include "effective_c++/lock.h"
namespace effective {
  //> Effective Modern C++ 19,关于使用shared_from_this的部分。
  /**
   * @brief The house class provide address for human living
   * @details The house class should not be derived
   */
  class House final : public Home, public std::enable_shared_from_this<House> {
  public:
    //> 这些默认成员函数需要删除，因为我们只对外提供一种创建House的方式。create()返回共享指针
    //> 这样可以使得registerHouse的share_from_this有效。也就是share_from_this使用前该类
    //> 的对象必须已经被shared_ptr接管，为了保证这一点只对外提供一种创建对象的方式create。
    //> 防止使用其他构造函数，得到一个不被shared_ptr管理的对象。
    House() = delete;
    House(const House& original) = delete;
    House& operator=(const House& right) = delete;
    House(House&& original) = delete;
    House& operator=(House&& right) = delete;
    virtual ~House() = default;
    /**
     * @brief Create house
     * @param name The shared poiter of the house.
     */
    static std::shared_ptr<House> create(std::string address);
    /**
     * @brief Register house. Add this house to the registered_houses_.
     */
    void registerHouse();

  private:
    virtual std::string doHealthValue() const override;
    virtual std::string doDraw(int color) const override;
    virtual std::string onTick() const override;
    explicit House(std::string address);
    std::vector<std::shared_ptr<House>> registered_houses_;
    Lock key;  // This key is used by animal, only one animal could stay in the House at one time.
  };
}  // namespace effective
#endif  // EFFECTIVE_HOUSE_H_