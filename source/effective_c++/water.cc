#include "effective_c++/water.h"

#include <string>

using namespace effective;
using std::string;
//> 因为头文件"person.hpp"中只有Person::Impl的声明，没有实现，编译时Person::Impl是一个不完整的类型，
//> 所以如果编译器在头文件中自动合成的特殊函数需要进行类型完整性检查则会导致编译失败！
//> 下面是编译器自动生成的特殊函数的行为：
//> 析构函数: std::unique_ptr<Person::Impl>使用默认的deleter，调用delete之前，会用static_assert
//> 在编译阶段对Person::Impl进行类型完整性检查，确保内部裸指针不会指向一个不完整的类型。 >
//> 移动赋值操作符：在赋值之前，需要销毁赋值操作符左边的Person对象，
//> 而销毁时需要对Person::Impl进行类型完整性检查。
//> 移动构造函数：编译器通常会在出现异常时生成销毁Person对象，
//> 而销毁时需要对Person::Impl进行类型完整性检查。
//> 拷贝构造函数和拷贝赋值操作符：默认产生的是浅拷贝,
//> 只拷贝了std::unique_ptr；而我们可能需要深拷贝，拷贝指针指向的内容。
//> 编译器自动生成的析构函数、移动赋值操作符和移动构造函数需要对Person::Impl进行类型完整性检查，
//> 所以应该放置在源文件中；而编译器自动生成的拷贝构造函数和拷贝赋值操作符采用的是浅拷贝，
//> 如果要实现深拷贝也应该在源文件中定义。
struct Water::Impl {
  std::string ingredient;
  std::string river;
};

Water::Water() : pimpl_(std::make_unique<Impl>()) {}

Water::~Water() = default;

Water::Water(Water&& rhs) = default;

Water& Water::operator=(Water&& rhs) = default;

Water::Water(const Water& rhs) : pimpl_(std::make_unique<Impl>(*rhs.pimpl_)) {}

Water& Water::operator=(const Water& rhs) {
  *pimpl_ = *rhs.pimpl_;
  return *this;
};