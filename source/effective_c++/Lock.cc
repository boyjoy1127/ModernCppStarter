#include "effective_c++/lock.h"

#include <mutex>

using namespace effective;
using std::mutex;

//> unlock()作为删除器传递给mutex_ptr_，当mutex_ptr_的引用计数为0时会调用此删除器，由于指定了删除器
//> 所以，count为0时候的动作就不是删除资源mutex，而是unlock mutex。
void unlock(mutex* mutex_ptr) { mutex_ptr->unlock(); }
//> 构造函数中初始化mutex_ptr_智能指针的时候，指定删除器，也就是智能指针析构时的操作。
//> 自定义删除器的作用是在智能指针释放所管理的对象时，执行一些特殊的操作。
//> 这样的实现可以使得Lock支持复制操作，复制时依赖mutex_ptr_管理mutex的引用计数。
Lock::Lock(mutex* mutex_ptr) : mutex_ptr_(mutex_ptr, unlock) {
  mutex_ptr_.get()->lock();
  users = new std::string[INT16_MAX];
}
//> delete[]与new[]需要成对使用。
Lock::~Lock() { delete[] users; }

std::mutex* Lock::get() const { return mutex_ptr_.get(); }
