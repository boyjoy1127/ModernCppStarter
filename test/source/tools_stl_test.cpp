#include "effective_c++/stl/tools_stl.h"

#include <functional>

#include "doctest/doctest.h"

TEST_CASE("Fib") {
  using namespace effective;
  const int result = Fib<10>::value;
  CHECK(result == 89);
}

TEST_CASE("IsSame") {
  using namespace effective;
  const bool result = is_same<int, int>::value;
  CHECK(result == true);
}

TEST_CASE("IsSame") {
  using namespace effective;
  const bool result = is_same<int, bool>::value;
  CHECK(result == false);
}

TEST_CASE("LogicalCalculate") {
  using namespace effective;
  const int result = TestLogicalCalculateTemplate(1);
  CHECK(result == 1);
}

TEST_CASE("IsSmaeNew") {
  using namespace effective;
  const bool result = is_same_new<int, int>::value;
  CHECK(result == true);
}

TEST_CASE("IsSmaeNew") {
  using namespace effective;
  const bool result = is_same_new<int, bool>::value;
  CHECK(result == false);
}

TEST_CASE("Conjunction") {
  using namespace effective;
  const bool result = conjunction<true_value, true_value, false_value>::value;
  CHECK(result == false);
}

TEST_CASE("Disjunction") {
  using namespace effective;
  const bool result = disjunction<true_value, true_value, false_value>::value;
  CHECK(result == true);
}

TEST_CASE("EnableIfConjunctionDisjunction") {
  using namespace effective;
  TestConjunctionDisjunction<double,
                             double>();  // 只有模板类型相同，且为float或double才可以编译通过
  // test<double, int>();  // 编译报错
}

TEST_CASE("TestConditional") {
  using namespace effective;
  int a = 0;
  CHECK(TestConditional<int>(a) == a);  // 只有模板类型相同，且为float或double才可以编译通过
}

TEST_CASE("TestConditionalNew") {
  using namespace effective;
  int a = 0;
  CHECK(TestConditionalNew<int>(a) == a);  // 只有模板类型相同，且为float或double才可以编译通过
}

TEST_CASE("RemoveConst") {
  using namespace effective;
  std::remove_const_t<int> a1 = 0;  // int
  CHECK(a1 == 0);
}

TEST_CASE("TestDecay") {
  using namespace effective;
  TestDecay t{"abc"};  // 推导出Test<char[4]>类型,实际调用的构造函数类型为Test(const char (&t)[4])
  // 推导出Test<char[4]>类型，但传参时通过decay，实际调用的构造函数是Test(const char * const &t)
  TestDecay2 t2{"abc"};
}

int TestFuncReturnType() { return 0; }
double TestArg2Type(int a, float b, double c) { return a + b + c; }
TEST_CASE("TestFuncReturnTypeAndArg2Type") {
  using namespace effective;
  struct T1 {
    int m();
  };
  struct T2 {
    int operator()();
  };
  // 函数类型
  GetRet_t<decltype(TestFuncReturnType)> a;
  // 函数指针类型
  GetRet_t<decltype(&TestFuncReturnType)> b;
  // 仿函数类型
  GetRet_t<T2> c;
  // lambda类型
  auto lc = []() -> int { return 0; };
  GetRet_t<decltype(lc)> d;
  // 非静态成员函数类型
  GetRet_t<decltype(&T1::m)> e;
  // 函数对象类型
  GetRet_t<std::function<int()>> g;

  CHECK(std::is_same_v<std::decay_t<decltype(a)>, int>);  // true
  CHECK(std::is_same_v<std::decay_t<decltype(b)>, int>);  // true
  CHECK(std::is_same_v<std::decay_t<decltype(c)>, int>);  // true
  CHECK(std::is_same_v<std::decay_t<decltype(d)>, int>);  // true
  CHECK(std::is_same_v<std::decay_t<decltype(e)>, int>);  // true
  CHECK(std::is_same_v<std::decay_t<decltype(g)>, int>);  // true

  Get2ndArg_t<decltype(TestArg2Type)> f;
  CHECK(std::is_same_v<std::decay_t<decltype(f)>, float>);
}

// 以下是TestHasMemberF
struct TestHasMemberF1 {
  static int f;  // 符合条件
};
struct TestHasMemberF2 {
  static double f;  // 含有f但类型不匹配
};
struct TestHasMemberF3 {};
// struct TestHasMemberF4 {
//   int f;  // 符合条件，非静态int成员
// };
TEST_CASE("TestHasMemberF") {
  using namespace effective;
  // 不含f
  CHECK(HasMemberF_v<TestHasMemberF1> == 1);  // 1
  CHECK(HasMemberF_v<TestHasMemberF2> == 0);  // 0
  CHECK(HasMemberF_v<TestHasMemberF3> == 0);  // 0
  CHECK(HasMemberF_v<int> == 0);              // 0
  // CHECK(HasMemberF_v<TestHasMemberF4> == 1);
}
// 以下是TestHasMemberF
struct HasMemberFWithoutLimitF1 {
  static int f;  // 符合条件
};
struct HasMemberFWithoutLimitF2 {
  int f();  // 含有f但类型不匹配
};
struct HasMemberFWithoutLimitF3 {
  double m();  // 含有f但类型不匹配
};
TEST_CASE("TestHasMemberFWithoutLimit") {
  using namespace effective;
  CHECK(HasMemberFWithoutLimit_v<HasMemberFWithoutLimitF1> == true);   // 1
  CHECK(HasMemberFWithoutLimit_v<HasMemberFWithoutLimitF2> == true);   // 1
  CHECK(HasMemberFWithoutLimit_v<HasMemberFWithoutLimitF3> == false);  // 0
}
