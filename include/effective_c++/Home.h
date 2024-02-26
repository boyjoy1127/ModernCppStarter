#pragma once
#ifndef EFFECTIVE_HOME_H_
#  define EFFECTIVE_HOME_H_
#  include <string>

#  include "clock.h"

namespace effective {
  /**
   * @brief The Home class provide address for animal living
   * @details The Home class should not be derived
   */
  class Home : private Clock {
    //> 按照public，protected，private的顺序进行声明，访问范围内部按照先函数后变量的方式排布。
  public:
    //> 使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
    //> 这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他
    //> 默认成员函数不再生成，造成错误。
    Home() = default;
    Home(const Home& original) = default;
    Home& operator=(const Home& right) = default;
    //> 可以使用delete删除默认成员函数。
    Home(Home&& original) = delete;
    Home& operator=(Home&& right) = delete;

    /**
     * @brief This is a deconstructor function.
     */
    virtual ~Home();

    /**
     * @brief Construct the Home object with name and weight.
     * @param name The name of the Home.
     */
    explicit Home(std::string address);  //>此处使用explicit防止单参构造函数用于隐式类型转换

    virtual std::string GetAddress() { return address_; };

    std::string GetAddress(std::string decorate) { return decorate + address_; };
    //> 此为NVI(non-virtual interface)手法，它使用了模板方法设计模式。
    //> healthValue称为doHealthValue的包装器。
    //> 除了用模板方法可以替代virtual函数。也可以采用策略模式+函数指针/函数对象，来实现。
    //> 具体参考Effective C++ Item35.
    int healthValue() const;
    //> 这里定义draw为public non-virtual带有默认参数，因为带有默认参数的函数不适合定义为虚函数
    //> 所以这里定义doDraw()为virtual，它在draw()中被调用。让派生类可以重写doDraw()。
    //> 这就是Effective C++ Item37中提倡的行为。
    void draw(int color = 1) const;
    // boardcast the address to the habitant.
    void boardcastAddress() const;

  protected:
    std::string address_;

  private:
    //> doHealthValue是private级别，派生类访问不到，但是派生类可以重写属于自己的函数。
    //> healtValue根据派生类对象调用对应的doHealthValue()函数。
    virtual int doHealthValue() const;
    virtual void doDraw(int color) const = 0;
    //> 通过私有继承方式重写onTick，可以防止Home的调用者调用onTick。
    //> 且私有继承表明 Home is not a Clock。
    //> 不过这种写法虽然可以防止Home派生类调用onTick(),但无法防止Home的派生类重写onTick。
    //> 定义内部类public继承Clock，并声明内部定义类型的成员变量。可以组织派生类重写onTick。
    //> 具体参考EffectiveC++ Item39
    //> 私有成员函数和成员变量，都是用//进行注释。
    // This function is responsible for sending the location of the broadcaster at regular
    // intervals to help the animal to find its way home.
    virtual void onTick() const;
    //> 当只想继承并重写某个虚函数的时候，可以用一下方法：
    //> 定义转交函数，私有继承+重写的方式，可以选择只继承Clock的tick()函数。
    //> Clock::stop()私有继承体系下不会被暴露出去。
    // Override tick from Clock. The class only need tick() to support the implementation of
    // boardcastAddress fucntion.
    virtual void tick() const;
  };
}  // namespace effective
#endif  // EFFECTIVE_HOME_H_