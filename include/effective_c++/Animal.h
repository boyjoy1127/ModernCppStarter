//> #pragma once 和 #ifndef作用都是为了避免同一个被 #include
//> 多次，或者避免头文件嵌套包含（参照前置声明的笔记）。需要特别注意的是：
//>（1）#pragma once
//> 并不是C++的原生语法，而是编译器的一种支持，所以并不是所有的编译器都能够支持。
//> #ifndef 则为C++的标准。
//> 2）#ifndef 依赖于不重复的宏名称，保证了包含在 #endif
//> 的内容不会被重复包含，这个内容可以是一个文件的所有内容，
//> 或者仅仅是一段代码。不过，它存在一个缺点就是，如果不同文件中的宏名撞车，
//> 那么就会可能导致你看到头文件明明存在，编译器却提示找不到。
//> 由于编译器每次都需要打开头文件才能判断是否有重复定义，在大型项目，可能使得编译时间变长。
//> #pragma once 则是针对物理文件的一个标记，标记该文件不会被 #include 多次，
//> 不能只针对文件中某段代码进行标记。而且，#pragma once 不能保证多个文件的拷贝不会被重复包含，
//> 也就是说当一份内容被拷贝到两个文件以后，这两个文件会被分别编译一次。但这种错误更容易发现，且
//> #pragma once 大大提高了编译效率。
//> 3）#pragma once目前被多数编译器支持，但由于不是C++标准，还是可能出现不被支持的情况。
//> 所以推荐的方式是把#pragma once写在头部，把#ifndef写到第二行。这样#pragma
//> once保证了效率，#ifndef提高了容错能力。 由于#pragma
//> once不是C++标准，所以不确定未来新的编译器是否会支持，或者原来的编译器改成不支持它。
#pragma once
#ifndef EFFECTIVE_ANIMAL_H_
#  define EFFECTIVE_ANIMAL_H_
#  include <string>

//> 头文件中不适用using,因为头文件的内容会拷贝到所有引用它的文件中去，如果头文件里有某个using声明，
//> 那么每个使用了该头文件的文件就都会有这个声明，从而可能产生名字冲突。
// using std::string;

namespace effective {
  /**
   * @brief The Animal class is a base class.
   * @details The Animal class should only be derived and could not be instantiated.
   */
  class Animal {
  public:
    //> 使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
    //> 这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他
    //> 默认成员函数不再生成，造成错误。
    Animal() = default;
    Animal(const Animal& original) = default;
    Animal& operator=(const Animal& right) = default;
    Animal(Animal&& original) = default;
    Animal& operator=(Animal&& right) = default;

    /**
     * @brief This is a virtual function that needs to be overloaded by derived classes.
     */
    virtual ~Animal() = 0;

    /**
     * @brief Construct the Animal object with name and weight.
     * @param name The name of the animal.
     * @param weight The weight of the animal.
     */
    Animal(std::string name, int weight);

    /**
     * @brief Construct the Animal object with name and weight.
     * @param name The name of the animal.
     */
    explicit Animal(std::string name);  //>此处使用explicit防止单参构造函数用于隐式类型转换

    /**
     * @brief Get description of the specific animal.
     * @param hava_weight The parameter decide whether put the weight in the result.
     * @return The result contains the name and the weight which depends on have_weight.
     */
    //>成员函数的定义出现在头文件中，那么该函数往往被编译默认器处理成inline，也可以人工添加inline显示标注。
    std::string GetDescription(bool hava_weight) {
      if (hava_weight) {
        return information_;
      }
      return name_;
    }

    /**
     * @brief Take a rest. The function needs to be overlo
     * @return Whether already sleeping.
     */
    virtual bool Sleep() = 0;

  protected:
    std::string name_;
    int weight_;
    std::string information_;
  };
}  // namespace effective
#endif  // EFFECTIVE_ANIMAL_H_