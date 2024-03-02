#pragma once
#include <memory>
#ifndef EFFECTIVE_HOME_FACTORY_H_
#  define EFFECTIVE_HOME_FACTORY_H_
#  include <iostream>
#  include <string>
#  include <unordered_map>

#  include "effective_c++/home/cave.h"
#  include "effective_c++/home/home.h"
#  include "effective_c++/home/nest.h"
namespace effective {
  //> Effective Modern C++ Item18
  /**
   * @brief The HomeFactory class produced kinds of home derived classes.
   * @details Produced kinds of home derived classes.
   */
  class HomeFactory {
  public:
    //> 声明成constexpr是为了保证它是编译期可见的，这样才能让依赖它的模板函数在编译器可以通过编译。
    //> 声明成static是希望它可以脱离HomeFactory对象的调用依赖，可以直接以函数形式被调用。
    /**
     * @brief This function is a deleter for unique_pointer.
     * @param home Home pointer type.
     */
    constexpr static auto delHome = [](Home* home) {
      std::cout << "Record once.";
      delete home;
    };
    /**
     * @brief This function returm derived class of home class.
     * @param type the type of the derived class.
     * @return The return type is std::unique_ptr<Home, decltype(delHome)>, it points to a derived
     * class.
     */
    //> C+=14下函数返回类型的推导可以编译器完成，因此函数返回类型可以声明为auto。
    //> 但是因为设计到模板编程，所以此类的实现应该放到头文件中，这样调用者依赖了头文件，
    //> 调用者的代码在编译期才能通过编译。
    auto makeHome(std::string type) {
      std::unique_ptr<Home, decltype(delHome)> result(nullptr, delHome);
      if (type == "Nest") {
        result.reset(new Nest("ParaNest"));
      } else if (type == "Cave") {
        result.reset(new Cave("ParaMountain"));
      }
      return result;
    }
    /**
     * @brief Get home by type from cache.
     * @param type the type of the home.
     * @return The return type is shared_ptr, it points to a home.
     */
    std::shared_ptr<Home> getHome(std::string type);
    /**
     * @brief Get the cache size.
     * @return The return the size of the cache.
     */
    int getCacheSize();

  private:
    std::unordered_map<std::string, std::weak_ptr<Home>> cache;
  };
}  // namespace effective
#endif  // EFFECTIVE_HOME_FACTORY_H_