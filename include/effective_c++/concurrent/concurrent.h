#pragma once
#ifndef EFFECTIVE_CONCURRENT_H_
#  define EFFECTIVE_CONCURRENT_H_
#  include <future>
namespace effective {
  //>这里对应Effective Modern C++ 37Item
  class ThreadRAII {
  public:
    enum class DtorAction { join, detach };  // enum class的信息见条款10

    ThreadRAII(std::thread&& t, DtorAction a)  // 析构函数中对t实行a动作
        : action(a), t(std::move(t)) {}

    ~ThreadRAII() {  // 可结合性测试见下
      if (t.joinable()) {
        if (action == DtorAction::join) {
          t.join();
        } else {
          t.detach();
        }
      }
    }

    std::thread& get() { return t; }     // 见下
    ThreadRAII(ThreadRAII&&) = default;  // 支持移动
    ThreadRAII& operator=(ThreadRAII&&) = default;

  private:
    DtorAction action;
    std::thread t;
  };
}  // namespace effective
#endif  // EFFECTIVE_CONCURRENT_H_