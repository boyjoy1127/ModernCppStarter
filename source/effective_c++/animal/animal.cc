#include "effective_c++/animal/animal.h"

//> 不要导入整个命名空间std，因为会有符号名冲突。导入具体的符号可以将冲突范围最小化。
using std::string;
using std::to_string;
using namespace effective;

//> 初始化成员列表的方式效率较高，应该尽量采用此种方式进行成员变量初始化。
//> 列表中成员变量的顺序最好和成员变量声明的顺序保持一致。参考：Effective C++的第4节
//> 当使用列表中的成员初始化另一个成员，或者需要调用成员函数的时候，等其他复杂情况。
//> 请在函数体内{}进行初始化操作。参考：深度探索C++对象模型 2.4节
Animal::Animal(string name, int weight) : name_(name), weight_(weight) {
  information_ = name_ + to_string(weight_);
}

Animal::Animal(string name) : name_(name), weight_(0) { information_ = name_ + to_string(weight_); }