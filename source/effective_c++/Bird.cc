#include "effective_c++/bird.h"

#include <memory>

using std::make_unique;
using namespace effective;

Bird::Bird() : Animal(), feather_color_("red") {
  nest_ptr_ = make_unique<Nest>();
  location_ = new int[2];
}

bool Bird::Sleep() { return true; }

void Bird::Fly() {
  location_[0] += 10;
  location_[1] += 10;
};

//> 因为成员变量都是内置类型，所以不需要在析构函数中操作释放内存
//> 源文件的虚析构函数的函数头不需要加virtual
//> 析构函数中主要处理一些内存堆资源的释放，或者文件句柄的释放，网络连接的关闭，锁的释放等。
Bird::~Bird() {
  // nest_ptr不再是裸指针，智能指针不需要显示删除，它会在离开作用域的时候自动消除。
  // delete nest_ptr_;
}