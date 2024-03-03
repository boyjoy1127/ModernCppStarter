#pragma once
#ifndef EFFECTIVE_LOCK_H_
#  define EFFECTIVE_LOCK_H_
#  include <memory>
#  include <mutex>

namespace effective {
  /**
   * @brief The Lock class.
   * @details The Lock class is used to guard. The class could not be overloaded.
   */
  //> 这个类不能被继承使用final
  class Lock final {
  public:
    //> 单参构造函数防止出现隐式类型转换
    explicit Lock(std::mutex* mutex_ptr);
    Lock() = default;
    Lock(const Lock& original) = default;
    Lock& operator=(const Lock& right) = default;
    Lock(Lock&& original) = delete;
    Lock& operator=(Lock&& right) = delete;
    //> class析构函数（无论是编译器生成的，还是用户自定义的）会自动调用其非静态成员变量的析构函数。
    ~Lock();
    //> 有时候RAII需要将内部原始资源暴露出来，提供显示转换API。
    //> 也可以提供隐式转换operator()，但是隐式转换相对容易出错，建议尽量使用显示转换。
    std::mutex* Get() const;

  private:
    //> RAII类只需要一个共享指针成员变量，就可以实现reference-counting copying的行为。
    std::shared_ptr<std::mutex> mutex_ptr_;
    std::string* users = new std::string[1];  // 足够大的一个string数组，存储哪些调用者持有此mutex
  };
}  // namespace effective
#endif  // EFFECTIVE_LOCK_H_