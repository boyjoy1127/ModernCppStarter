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
  std::string river = "IceRiver";
  int volume = 10;
};

Water::Water() : pimpl_(std::make_unique<Impl>()){};

Water::~Water() = default;

Water::Water(Water&& rhs) = default;

Water& Water::operator=(Water&& rhs) = default;

Water::Water(const Water& rhs) : pimpl_(std::make_unique<Impl>(*rhs.pimpl_)){};
//> Effective C++ 10: 为了实现连锁赋值，赋值操作符必须返回一个refernce to *this。
//> Effective C++ 11: 考虑到使用operator=进行自我赋值时的正确性，需要仔细考虑operator内部的实现。
//> 此处如果使用的是裸指针，则需要有更多的考虑，因为涉及到new和delete。
//> Effective C++ 12：拷贝构造和拷贝赋值在自定义实现时，需要完成每个元素的拷贝，
//> 如果是继承类，还需要调用base class的拷贝。不要另copy赋值函数调用copy构造函数，
//> 因为这样是在试图构造一个已经存在的对象，但是此对象由于尚未构建完成，调用它的拷贝构造函数会出错。
Water& Water::operator=(const Water& rhs) {
  *pimpl_ = *rhs.pimpl_;
  // this(rhs);//编译器会报错，无法调用拷贝构造函数
  return *this;
};

long Water::GetWater() const { return pimpl_->volume; }
