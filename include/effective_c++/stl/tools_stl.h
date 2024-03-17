#pragma once
#ifndef EFFECTIVE_ENABLE_IF_H_
#  define EFFECTIVE_ENABLE_IF_H_
#  include <iostream>
#  include <type_traits>
namespace effective {
  // 例子1
  // 当调用者使用enable_if<condition，int>::type时，
  // 如果condition为false则匹配失败，只有condition为true时才成功。
  // enable_if的功能当匹配到特化模板时，也就是cond为true，那么返回type值。
  // 当cond为false匹配到普通模板，且由于没有type定义，所以匹配失败。 template <bool cond,
  template <bool cond, typename T = void> struct enable_if {};

  template <typename T> struct enable_if<true, T> {
    using type = T;
  };
  // 例子2
  // 整数运算
  template <int N> struct Fib {
    constexpr static int value = Fib<N - 2>::value + Fib<N - 1>::value;
  };

  template <> struct Fib<0> {
    constexpr static int value = 1;
  };

  template <> struct Fib<1> {
    constexpr static int value = 1;
  };
  // 例子3
  // 逻辑运算
  template <typename T1, typename T2> struct is_same {
    constexpr static bool value = false;
  };

  template <typename T> struct is_same<T, T> {
    constexpr static bool value = true;
  };
  // 下面是一个demo，利用enable_if，当参数为int时才生效
  template <typename T>
  typename std::enable_if<is_same<T, int>::value, int>::type TestLogicalCalculateTemplate(T t) {
    return t;
  }
  // 例子4
  // 像上面这样把value展开来写会比较长，容易出错，也降低了一些可读性。
  // 把计算属性的部分抽象出了一个基类，同时，又给布尔类型的实例起了别名
  template <typename T, T val>  // 注意这里的写法
  struct integer_constant {
    constexpr static T value = val;
  };
  // 对布尔类型的实例单独起名
  template <bool val> using bool_constant = integer_constant<bool, val>;
  using true_value = bool_constant<true>;
  using false_value = bool_constant<false>;
  template <typename T1, typename T2> struct is_same_new : false_value {};
  template <typename T> struct is_same_new<T, T> : true_value {};
  // 例子5
  // 逻辑运算，取反。
  // 这样一来，negation<true_value>会得到false_value，
  // negation<false_value>会得到true_value，而对于其他类型的negation<T>则会命中通用模板，
  // 并不含有value成员，用于表示此项不合法。
  template <typename T> struct negation {};
  template <> struct negation<true_value> : false_value {};
  template <> struct negation<false_value> : true_value {};

  // &&
  // 根据逻辑短路原则，如果T1是false_value，那么直接返回false_value；如果T1是true_value，那么结果跟T2保持一致。
  // 支持连续计算
  template <typename... Args> struct conjunction : false_value {};
  // 单独考虑仅一个true_value的情况
  template <> struct conjunction<true_value> : true_value {};
  // 多项的情况就是拆开，把第一项单独拿出来，如果第一项是true_value，那么就按后面的走，如果是false，此偏特化不命中，走向通用模板，而通用模板就是false_value
  template <typename... Args> struct conjunction<true_value, Args...> : conjunction<Args...> {};

  // ||
  // 根据逻辑短路原则，如果T1是true_value，那么直接返回true_value；如果T1是false_value，那么结果跟T2保持一致。
  // 支持连续计算
  template <typename... Args> struct disjunction : true_value {};
  template <> struct disjunction<false_value> : false_value {};
  template <typename... Args> struct disjunction<false_value, Args...> : disjunction<Args...> {};

  // 联合enable if，conjunction，disjunction
  template <typename T1, typename T2> typename std::enable_if<
      std::conjunction<std::disjunction<std::is_same<T1, float>, std::is_same<T1, double>>,
                       std::disjunction<std::is_same<T2, float>, std::is_same<T2, double>>>::value,
      void>::type
  TestConjunctionDisjunction(){};

  // 类型处理
  // 例子1
  // conditional是一个用于类型处理的辅助类，它拥有3个参数，第一个参数是一个静态布尔值，
  // 用于表示判断条件；后两个参数是用于选择的类型。当条件为真时，type成员会定义为前一个类型；
  // 当条件为假时，type成员会定义为后一个类型。
  // 与前面介绍的value同理，这里的type也是STL中约定的命名方式，原则上可以不遵守，
  // 但倡导大家来遵守。type表示的就是这个辅助类的输出，既然这个辅助类的作用是「类型处理」，
  // 那么自然要输出一个类型。
  // 在使用的Demo中我们可以看到，conditional<xxx, T, const T
  // &>就是这里的辅助类型，而里面的xxx就需要一个静态布尔值。
  // 我们在这里用std::is_fundamental来判断一个类型是不是基本数据类型。取std::is_fundamental<T>::value获取这个判断的结果。
  // 再取conditional<xxx, T, const T &>::type用来获取类型处理的结果。
  // 值得注意的是，conditional<xxx, T1, T2>本身是一种类型，但这个是辅助类本身的类型，
  // 而要通过辅助类拿到类型处理的结果类型则是要取一次type，也就是typename conditional<xxx, T1,
  // T2>::type。
  template <bool cond, typename T1, typename T2> struct conditional {
    using type = T1;
  };
  template <typename T1, typename T2> struct conditional<false, T1, T2> {
    using type = T2;
  };
  template <typename T>
  typename conditional<std::is_fundamental<T>::value, T, const T &>::type TestConditional(
      typename conditional<std::is_fundamental<T>::value, T, const T &>::type t) {
    return t;
  };
  // 例子2
  // 针对is_fundamental写的辅助工具
  // 相信大家应该已经发现了，使用这些辅助类型，再取成员（value或者type）会让代码迅速变长，尤其是取type的时候，
  // 还要加上typename，这玩意要是有嵌套的话，可读性会直接炸掉。因此，推荐的做法是针对这些辅助类搭配一个辅助工具，
  // 让代码变短，增强可读性。
  template <typename T> constexpr inline bool is_fundamental_v = std::is_fundamental<T>::value;
  // 针对conditional写的辅助工具
  template <bool cond, typename T1, typename T2> using conditional_t =
      typename conditional<cond, T1, T2>::type;
  template <typename T> conditional_t<is_fundamental_v<T>, T, const T &> TestConditionalNew(
      conditional_t<is_fundamental_v<T>, T, const T &> t) {
    return t;
  };

  // 在STL中，C++17标准下所有的模板元都配置了对应的辅助工具，用于数值计算的配备了对应_v结尾的工具，用于获取value；
  //  用于类型处理的配备了对应_t结尾的工具，用于获取type。所以上面的Demo如果完全使用STL则应该是：
  // void f(std::conditional_t<std::is_fundamental_v<T>, T, const T &> t) {}

  // 变类型的类型处理
  // 我希望提供一个用于去掉const的工具，也就是说，如果一个类型有const修饰，那么返回去掉const后的类型，如果没有的话就原样返回。
  // 这里要注意的是，「一个类型有const修饰」是指这个类型本身，而不包括它内部含有的类型。举例来说，const
  // int *并没有用const修饰，
  // 因为这个类型本身是指针类型，而const修饰的是它的解指针类型。因此它去掉const后应该还是它本身。而int
  // *const类型才是用const修饰的，
  // 应当变换为int *。同理，const int *const应当变为const int *。再同理，const int
  // &也应当是原样输出。
  template <typename T> struct remove_const {
    using type = T;
  };
  template <typename T> struct remove_const<const T> {
    using type = T;
  };
  // 辅助工具
  template <typename T> using remove_const_t = typename remove_const<T>::type;

  // 完全退化
  template <typename T> struct decay {
  private:
    using U = std::remove_reference_t<T>;

  public:
    using type = std::conditional_t<
        std::is_array_v<U>,
        std::remove_extent_t<U> *,  // 如果是数组就转指针
        std::conditional_t<std::is_function_v<U>,
                           std::add_pointer_t<U>,  // 如果是函数就转函数指针
                           std::remove_cv_t<U>     // 其他情况则去掉const和volatile
                           >>;
  };
  template <typename T> using decay_t = typename decay<T>::type;
  template <typename T> struct TestDecay {
    TestDecay(const T &t) { std::cout << sizeof(t); };
  };
  template <typename T> struct TestDecay2 {
    TestDecay2(std::decay_t<T> const &t) { std::cout << sizeof(t); }
  };
  // 这里由于构造参数和模板参数类型不一致，因此自动推导失效了，
  // 我们需要手动添加一个推导指南(deduction guides)：
  template <typename T> TestDecay2(T &) -> TestDecay2<std::decay_t<T>>;

  /*函数返回值类型*/
  template <typename T> struct GetRet {
  private:
    using DT = std::decay_t<T>;

  public:
    // 如果内部含有operator()就取它的类型
    using type = typename GetRet<decltype(&DT::operator())>::type;
  };

  // 对于函数类型
  template <typename R, typename... Args> struct GetRet<R(Args...)> {
    using type = R;
  };

  // 对于函数指针类型
  template <typename R, typename... Args> struct GetRet<R (*)(Args...)> {
    using type = R;
  };

  // 对于非静态成员函数类型
  template <typename T, typename R, typename... Args> struct GetRet<R (T::*)(Args...)> {
    using type = R;
  };
  template <typename T, typename R, typename... Args> struct GetRet<R (T::*)(Args...) const> {
    using type = R;
  };
  template <typename T> using GetRet_t = typename GetRet<T>::type;

  /*获取函数参数*/
  template <typename T> struct Get2ndArg {
  private:
    using DT = std::decay_t<T>;

  public:
    // 如果内部含有operator()就取它的类型
    using type = typename Get2ndArg<decltype(&DT::operator())>::type;
  };

  template <typename R, typename Arg1, typename Arg2, typename... Args>
  struct Get2ndArg<R(Arg1, Arg2, Args...)> {
    using type = Arg2;
  };

  template <typename R, typename Arg1, typename Arg2, typename... Args>
  struct Get2ndArg<R (*)(Arg1, Arg2, Args...)> {
    using type = Arg2;
  };

  template <typename T, typename R, typename Arg1, typename Arg2, typename... Args>
  struct Get2ndArg<R (T::*)(Arg1, Arg2, Args...)> {
    using type = Arg2;
  };

  template <typename T, typename R, typename Arg1, typename Arg2, typename... Args>
  struct Get2ndArg<R (T::*)(Arg1, Arg2, Args...) const> {
    using type = Arg2;
  };

  template <typename T> using Get2ndArg_t = typename Get2ndArg<T>::type;

  /*判断类型T中是否有int类型的成员*/
  // 着重解释一下这里的写法，首先，通用模板中含有2个参数，但是第二个参数V是用做辅助参数的，
  // 我们给它默认参数为int。之后，其实我们是要给HasMemberF<T, int>来绑定true_type的。
  // 但仅当T::f的类型是int时才生效。
  // 详细参考https://blog.csdn.net/fl2011sx/article/details/128864369，解释了过程原理，值得仔细阅读
  template <typename T, typename V = int>  // V是辅助参数
  struct HasMemberF : std::false_type {};  // 判断T中是否函数f成员
  template <typename T> struct HasMemberF<T, decltype(T::f)> : std::true_type {};
  // 如果想获取数据结构中的非静态类型，可以这样使用。但是这个模板不能与静态类型的声明同时存在，所以注释掉了。
  //  template <typename T> struct HasMemberF<T, decltype(std::declval<T>().f)> : std::true_type {};
  // 如果我要求只想筛选出非静态的怎么办？那就只能通过取地址的方式拿出成员变量了（&T::f取出成员的指针类型）
  // template <typename T> struct HasMemberF<T, decltype(&T::f)> : std::true_type {};
  template <typename T> constexpr inline bool HasMemberF_v = HasMemberF<T>::value;

  // 判断类型中是否含有某个成员，名称为f，不限制函数和变量。
  template <typename T, typename V = void> struct HasMemberFWithoutLimit : std::false_type {};
  template <typename T> struct HasMemberFWithoutLimit<T, std::void_t<decltype(&T::f)>>
      : std::true_type {};
  template <typename T> constexpr inline bool HasMemberFWithoutLimit_v
      = HasMemberFWithoutLimit<T>::value;
}  // namespace effective
#endif  // EFFECTIVE_ENABLE_IF_H_