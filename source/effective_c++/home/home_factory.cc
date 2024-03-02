#include "effective_c++/home/home_factory.h"

using std::string;
using namespace effective;

std::shared_ptr<Home> HomeFactory::getHome(std::string type) {
  // std::weak_ptr::lock 会返回一个shared_ptr
  auto home_weak_ptr = cache[type];
  auto home_shared_ptr = home_weak_ptr.lock();
  if (!home_shared_ptr) {
    home_shared_ptr = makeHome(type);  // unique_ptr可以赋值给shared_ptr
    cache[type] = home_shared_ptr;     // shared_ptr可以赋值给weak_ptr
  }
  return home_shared_ptr;
}

int HomeFactory::getCacheSize() { return cache.size(); }
