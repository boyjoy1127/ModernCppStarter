C++语法查询 https://en.cppreference.com/w/
C++语法查询 https://c.biancheng.net/cplus/
ModernCppStarter项目中整理出来一个代码样例项目，将CGL、Modern EffectiveC++、EffectiveC++、More EffectiveC++的良好实践都整理进来。
Effective Modern C++版本：https://cntransgroup.github.io/EffectiveModernCppChinese/3.MovingToModernCpp/item7.html
本地下载Effective Modern C++的中文版，翻译的不太好。还是看github这个链接的中文版比较好。
*《深度探索C++对象模型》这本书详细讲解的了对象初始化、析构和内存布局，值得阅读*
书中的条款在项目中以注释的形式来搞。
以C++14作为规范

### 各个书籍已经阅读的部分
Effective C++：4,5,6,7,8,9,10,11,12,13,14,15,16,17,32,33,34,35,36,37,38,39,40.
More Effective C++：14,9,8,3,24,33.
Effective Modern C++：11,17,14,12,18,19,20,21,22.

### 面向对象语法
(按照这个顺序阅读添加：Effective C++(2,3,4,5,6)、More EffectiveC++(5,6,7)、Effective Modern C++(3)、CGL、)

#### 类的设计原则
**Effective C++ 19**
**提纲挈领**
设计class犹如设计type
C++程序员的很多时间多在扩张自己的类型系统(也就是编写各种class)，应该带着和“语言设计者当初设计语言内置类型时”一样的谨慎来研讨class的设计。好的types有自然的语法，直观的语义，一个或多个高效实现品。
1. 新type的对象应该如何被创建和销毁？
2. 对象的初始化,对象的赋值,对象的移动该有什么样的差别？
3. 新type的对象如何被pass by value，意味着什么？
4. 什么是新type的合法值？
5. 你的新type需要配合某个继承图系吗？
6. 你的新type需要什么样的转换？
7. 什么样的操作符和函数对此新type而言是合理的?
8. 什么样的标准函数应该驳回？
9. 谁该取用新type的成员？
10. 什么是新type的未声明接口？
11. 你的新type有多么一般化？
12. 你真的需要一个新type吗？

**More Effective C++ 32**
*值得多次阅读*
未来时态的考虑只是简单地增加了一些额外约束：
- 提供完备的类（见 Item E18），即使某些部分现在还没有被使用。如果有了新的需求，你不用回过头去改它们。
- 将你的接口设计得便于常见操作并防止常见错误（见 Item E46）。使得类容易正确使用而不易用错。例如，阻止拷贝构造和赋值操作，如果它们对这个类没有意义的话（见 Item E27）。防止部分赋值（见 Item M33）。
- 如果没有限制你不能通用化你的代码，那么通用化它。例如，如果在写树的遍历算法，考虑将它通用得可以处理任何有向不循环图。未来时态的考虑增加了你的代码的可重用性、可维护性、健壮性，已及在环境发生改变时易于修改。它必须与进行时态的约束条件进行取舍。太多的程序员们只关注于现在的需要，然而这么做牺牲了其软件的长期生存能力。是与众不同的，是离经叛道的，在未来时态下开发程序。


**Effective C++ 18**
让接口容易被正确使用，不易被误用。
好的接口很容易被正确使用，不容易被误用。你应该在你的所有接口中努力达成这些性质。
促进正确使用的办法包括接口的一致性，以及与内置类型的行为兼容。
“阻止误用”的办法，在函数参数类型和返回类型上：建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任。防止客户输入了错误的参数值，或者拿到返回值后使用不当(主要体现在指针上，所以推荐返回智能指针，减少客户手动删除资源的负担)。
推荐使用智能指针，智能指针支持定制型删除器，防止cross ddl时忘记删除资源的情况出现。

**Effective C++ 20**
函数的参数，尽量使用pass by reference to const替换pass by value，前者通常比较高效，并可避免切割问题。
以上规则不适用于内置类型，以及STL的迭代器和函数对象，对它们而言，pass by value往往比较适当。

**Effective C++ 21**
必须返回对象时，别返回引用。书写函数时很多时候下，返回值应该是对象。特殊情况才考虑用refernce和pointer。比如单例用reference，考虑到返回值复制效率太低而使用pointer。
绝对不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回point或reference指向
一个local static对象而有可能同时需要多个这样的对象。条款4已经为“在单线程环境中合理返回reference指向一个local static对象”提供了一份设计实例。

**Effective C++ 22**
将成员变量声明为private。如果想让成员被外部访问则将对应函数声明为public，如果只想让子类访问则将对应函数声明为protected。
切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者以充分的实现弹性。
protected并不比public更具封装性。

**Effective C++ 23**
宁可拿non-member且non-friend 函数替换member函数。这样做可以增加封装性、包裹性和机能扩充性。
*本节内容很好，对于封装性和封装方式，有了更多理解*

**Effective C++ 24**
所有参数皆需要转换类型，采用non-member且non-friend函数。
如果你需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member。
*和23条共同给出了应该使用non-member且non-friend函数的场景*

**Effective C++ 25**
考虑写出一个不抛出异常的swap函数
swap是一个很有用的函数，原本它只是STL的一部分。而后成为异常安全性编程的脊柱，
以及用来处理自我赋值可能性的一个常见机制。通常我们不能够改变std命名空间内的任何东西，但可以为标准templates制造特化版本，使它专属于我们自己的class。下面这种做法不只能通过编译，还与STL容器有一致性，因为所有STL容器也都提供有public swap成员函数和std::swap特化版本。
```cpp
class Widget{
public:
...
void swap(Widget& other){
	using std::swap;
	swap(pImpl, other.pImpl);
}
...
};

namespace std{
	template<> void swap<Widget> (Widget& a, Widget& b){
		a.swap(b);
	}
}
```
当std::swap对你的类型效率不高，提供一个swap成员函数，并确定这个函数不抛出异常。
如果你提供一个Member swap,也改提供一个non-member swap用来调用前者。对于classes，也请特化std::swap。
调用swap时应针对std::swap使用using声明式，然后调用swap并且不带任何“命名空间资格修饰”。
为“用户定义类型”进行std templates全特化是好的，但千万不要尝试的std内加入某些对std而言全新的东西。

#### 类的实现原则
**Effective C++ 26**
尽可能地延后变量定义式的出现时间。这样可增加程序的清晰度并改善程序效率。
在非循环逻辑中，要坚持延后声明和定义变量。
在循环逻辑中，也应该坚持延后声明和定义变量。除非，你的程序对于效率要去很高，需要你提前声明变量才能提高效率，才考虑不遵循这个原则，如下面这种情况，如果A中拷贝赋值函数的成本小于构造+析构，且我们的程序对效率要求很高，那么才选择A方法。一般选择B方法，因为B更加清晰。
```cpp
//方法A
Widget w;
for(inti =0;i<n;++i>){
	w = 取决于i的某个值；
}

//方法B
for(inti =0;i<n;++i>){
	Widget w(取决于i的某个值)；
}
```

**Effective C++ 27**
尽量少做转型动作。
如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_casts。如果有个设计需要转型动作，试着发展无需转型的替代设计。
如果转型是必要的，试着将它隐藏于某个函数背后。客户随后可以调用该函数，而不需将转型放进他们自己的代码内。
宁可使用C++STYLE(新式)转型，不要使用旧式转型。前者很容易识别出来，而且也比较有着分门别类的职掌。新式转换：
const_cast<T>:常量性剔除。
dynamic_case<T>:基类对象转换为派生类对象。
reinterpret_case<T>:从原始内存的二进制级别进行转换。比如将指针转换为int。
static_case<T>:int转double，void*指针转为typed指针，但是它无法将const转换为non-const.

**More Effective C++ 2**
尽量使用C++风格的类型转换。

**Effective C++ 28**
避免返回handles指向对象内部成分。Reference，指针和迭代器统统都是所谓的handles。遵守这条可增加封装性，帮助const成员函数的行为像个const，并将发生“虚吊号码牌”的可能性降至最低。

**Effective C++ 29**
为“异常安全”而付出的额外精力和代码都是值得的。
异常安全函数即使发生异常也不会泄露资源或允许任何数据结构败坏。这样的函数区分为三种可能的保证：基本型，强烈型，不抛异常型。
“强烈保证”往往能够以copy and swap实现出来，但“强烈保证”并非对所有函数都可实现或具备现实意义。
函数提供的“异常安全保证”通常最高只等于其调用之各个函数的“异常安全保证”中的最弱者。

**Effective C++ 31**
将文件间的编译依存关系降至最低
支持“编译依存性最小化”的一般构想是：相依于声明式，不要相依于定义式。在实现一个类的时候，通过声明式依赖第三方，可以降低编译依存性，如果第三方实现变了，我们作为调用者是不需要重新编译的。
Handle classes和Interface classes。解除了接口和实现之间的耦合关系，我们编写了一个接口类给外部用，当我们需要修改内部实现的时候，外部客户无需重新编译他们的代码。
程序库头文件应该以“完全且仅有声明式”的形式存在。这种做法不论是否设计templates都适用。
如果使用object references 或 object pointer可以完成任务，就不要使用objects。
如果能够，尽量以class声明式替换class定义式。
为声明式和定义式提供不同的头文件。
*何时使用这个方式减低编译依存性呢？*
使用Handle classes和Interface classes会对执行效率和内存消耗有一点额外影响，如果是在对计算速率和内存使用要求严苛的场景，则要谨慎考虑使用。它跟inline是相对，正确inline可以让程序跑得更快。
在有强烈降低编译时间的需求场景下，可以考虑使用这个方法。比如说编写了一个上百个函数的库，那么就应该考虑降低编译时间的需求，库中实现的时候尽量用声明方式依赖第三方，客户调用哪个函数再额外引入函数用到的一些第三方定义头文件。因为客户只使用其中的几个函数，没必要引入全部第三方依赖。
声明式是指“class Date”，定义式是指“class Date{}”。

**More Effective C++ 1**
指针和引用的区别，什么时候使用指针，什么时候使用引用？
当你知道你必须指向一个对象并且不想改变其指向时，或者在重载操作符并未防止不必要的语义误解时，你不该使用指针。而在除此之外的其他情况下，则应该使用指针。

**More Effective C++ 6**
自增自减操作符前缀形式与后缀形式的区别。
```cpp
class UPInt { // "unlimited precision int"
	public:
		UPInt& operator++(); // ++ 前缀
		const UPInt operator++(int); // ++ 后缀
		UPInt& operator--(); // -- 前缀
		const UPInt operator--(int); // -- 后缀
		UPInt& operator+=(int); // += 操作符，UPInts
		// 与 ints 相运算
		...
};
// 前缀形式：增加然后取回值
UPInt& UPInt::operator++()
{
	*this += 1; // 增加
	return *this; // 取回值
}
// postfix form: fetch and increment
const UPInt UPInt::operator++(int)
{
	UPInt oldValue = *this; // 取回值
	++(*this); // 增加
	return oldValue; // 返回被取回的值
}
```
很明显一个后缀 increment 必须返回一个对象（它返回的是增加前的值），但是为什么是 const 对象呢？假设不是 const 对象，下面的代码就是正确的：
```cpp
UPInt i;
i++++; //这是违反了内置类型的使用惯例的
```
如果你原来想过让一个函数返回 const 对象没有任何意义，现在你就知道有时还是有用的，后缀 increment 和 decrement 就是例子。 
从上述的例子中可以看出，后缀操作的代价更大，因为它需要额外的临时变量oldValue。
后缀和前缀应该完成一样的功能。这个原则是后缀increment 和 decrement 应该根据它们的前缀形式来实现。你仅仅需要维护前缀版本，因为后缀形式自动与前缀形式的行为一致。

**More Effective C++ 7**
不要重载 “&&” “||” 或 “,”
重载后，会使得“&&” “||”运算符不具备短路求值的特性。重载后，会使得“,”不具备先计算左侧表达式，后计算右侧表达式。

**Effective Modern C++ 5**
使用auto带来的好处：
1. 避免未初始化的变量，因为如果不初始化auto变量，编译器将报错。
2.避免变量类型声明和实际赋值类型不相符合时，引起的隐式类型转换的问题，auto使得变量声明类型和赋值类型相同。
3. 它可以直接持有封装体，也就是配合lamdba表达式配合使用。
auto是一个可选项，不是必选项。如果显示写清楚类型声明可以带来可读性增强的话，则可以考虑不使用auto。
auto 变量一定要被初始化， 并且对由于类型不匹配引起的兼容和效率问题有免疫力， 可以简单化代码重构， 一般会比显式的声明类型敲击更少的键盘。
auto 类型的变量也受限于条款2和条款6中描述的陷阱。

**Effective Modern C++ 6**
避免auto声明的变量，被一个对外部不可见的代理类类型变量赋值，如下：
```cpp
auto someVar = expression of "invisible" proxy class type;
```
当auto声明的变量被一个表达式赋值的时候，需要看看这个表达式返回的类型，如果是内部代理类则需要更多关注。
当auto推导出非预期类型时应该使用显示的类型初始化。
```cpp
std::vector<bool> features(const Widget& w);
Widget w;

bool highPriority = features(w)[5]; // 无问题

auto highPriority = features(w)[5]; // 有问题
// 如果使用auto，则应该这样写。这样写比直接声明变量类型为bool更好，因为它是一个显示类型转换，明确表达了需要转换的用意。
auto highPriority = static_cast<bool>(features(w)[5]);
// 未定义行为,因为highPriority的类型是std::vector<bool>::reference，而我们期望highPriority是bool
processWidget(w, highPriority); 
```

**Effective Modern C++ 7**
区别使用()和{}创建对象
现代C++推崇使用{}进行初始化，统一初始化的方式。
```cpp
int z{0};             //使用花括号初始化
std::vector<int> v{ 1, 3, 5 };  //v初始内容为1,3,5
std::atomic<int> ai1{0};
```
花括号初始化是最广泛使用的初始化语法，它防止变窄转换，并且对于C++最令人头疼的解析有天生的免疫性。	
```cpp
double x, y, z;
int sum1{ x + y + z };          //错误！double的和可能不能表示为int,仿真窄化。

Widget w2();                    //最令人头疼的解析！声明一个函数w2，返回Widget
Widget w3{};                    //调用没有参数的构造函数构造对象
```
当auto声明的变量使用花括号初始化，变量类型会被推导为std::initializer_list，但是使用相同内容的其他初始化方式会产生更符合直觉的结果。所以，你越喜欢用auto，你就越不能用括号初始化。

在构造函数重载决议中，编译器会尽最大努力将括号初始化与std::initializer_list参数匹配，即便其他构造函数看起来是更好的选择。
第一，作为一个类库作者，你需要意识到如果一堆重载的构造函数中有一个或者多个含有std::initializer_list形参，用户代码如果使用了括号初始化，可能只会看到你std::initializer_list版本的重载的构造函数。因此，你最好把你的构造函数设计为不管用户是使用圆括号还是使用花括号进行初始化都不会有什么影响。
std::initializer_list重载不会和其他重载函数比较，它直接盖过了其它重载函数，它重载函数几乎不会被考虑。所以如果你要加入std::initializer_list构造函数，请三思而后行。
```cpp
class Widget { 
public:  
    Widget(int i, bool b);      //同上
    Widget(int i, double d);    //同上
    Widget(std::initializer_list<long double> il);      //新添加的
    …
};

Widget w1(10, true);    //使用圆括号初始化，同之前一样
                        //调用第一个构造函数

Widget w2{10, true};    //使用花括号初始化，但是现在
                        //调用带std::initializer_list的构造函数
                        //(10 和 true 转化为long double)

Widget w3(10, 5.0);     //使用圆括号初始化，同之前一样
                        //调用第二个构造函数 

Widget w4{10, 5.0};     //使用花括号初始化，但是现在
                        //调用带std::initializer_list的构造函数
                        //(10 和 5.0 转化为long double)

```
在模板类选择使用圆括号初始化或使用花括号初始化创建对象是一个挑战。需要明确使用圆括号还是花括号。标准库函数std::make_unique和std::make_shared（参见Item21）面对的问题。它们的解决方案是使用圆括号，并被记录在文档中作为接口的一部分。


**Effective Modern C++ 8**
NULL就是0，是个宏。`#define NULL 0`
nullptr不是指针类型。，nullptr的类型为std::nullptr_t，因为 std::nullptr_t 可以隐式转换为任何类型的指针。
- 优先使用nullptr而不是0或者null。nullptr明确表明是一个空指针。
nullptr 可以使得代码逻辑更加清晰，可见下面：
```cpp
auto result = findRecord( /* arguments */);
if(result == 0){
	...
}
//如果你不能轻松地的看出 findRecord 返回的是什么， 要知道 result 是一个指针还是整数类
//型并不是很简单的。 毕竟， 0 （ 被用来测试 result 的） 即可以当做指针也可以当做整数类型。 
auto result = findRecord( /* arguments */);
if(reuslt == nullptr){//明显就没有歧义了： result 一定是个指针类型
	...
}
```
nullptr很适合用在模板中，用于类型推导。
```cpp
int f1(std::shared_ptr<Widget> spw); // 只有对应的
double f2(std::unique_ptr<Widget> upw); // 互斥量被锁定
bool f3(Widget* pw); // 才会调用这些函数

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
{
	MuxGuard g(mutex);
	return func(ptr);
}
auto result1 = lockAndCall(f1, f1m, 0); // 错误, 0被推导为int，与f1函数要求的入参不同。
auto result2 = lockAndCall(f2, f2m, NULL); // 错误，NULL被推导为整型，与f2函数要求的入参不同。
auto result3 = lockAndCall(f3, f2m, nullptr); // 正确
```
- 避免整数类型和指针类型之间的重载。如果一个函数有整数和指针的重载，考虑使用nullptr而不是NULL来调用。
```cpp
void f(int); // 函数f的三个重载
void f(bool);
void f(void*);
f(0); // 调用 f(int)， 而非f(void*)
f(NULL); // 可能无法编译， 但是调用f(int),不可能调用 f(void*)
```


**Effective Modern C++ 9**
- 优先使用声明别名而不是typedef
```cpp
//c++ 98的方式
typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;
//C++ 11的方式
using UptrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;

// FP等价于一个函数指针， 这个函数的参数是一个int类型和std::string常量类型， 没有返回值
typedef void (*FP)(int, const std::string&); // typedef
using FP = void (*)(int, const std::string&); // 声明别名，这个方式可读性好。
```
- typedef不支持模板化，但是别名声明支持。
```cpp
//使用using很简单
template<typname T> // MyAllocList<T>
using MyAllocList = std::list<T, MyAlloc<T>>; // 等同于// std::list<T, MyAlloc<T>>
MyAllocList<Widget> lw; // 终端代码

//使用typedef就比较繁琐了
template<typename T> // MyAllocList<T>::type
struct MyAllocList { // 等同于
	typedef std::list<T, MyAlloc<T>> type; // std::list<T,MyAlloc<T>>
}; 
MyAllocList<Widget>::type lw; // 终端代码

//这里MyAllocList<T>::type使用了一个类型，这个类型依赖于模板参数T。因此MyAllocList<T>::type是一个依赖类型（dependent type)
//在依赖类型的名称之前必须冠以 typename 
template<typename T>
class Widget {                              //Widget<T>含有一个MyAllocLIst<T>对象作为数据成员
private:                                    
    typename MyAllocList<T>::type list;     
    …
}; 

//如果使用using则简单一些。
//当编译器处理Widget模板时遇到MyAllocList<T>（使用模板别名声明的版本），它们知道MyAllocList<T>是一个类型名，
//因为MyAllocList是一个别名模板：它一定是一个类型名。因此MyAllocList<T>就是一个非依赖类型（non-dependent type），
//就不需要也不允许使用typename修饰符。
template<typename T>
class Widget {
	private:
	MyAllocList<T> list; // 没有typename，因为编译器很容易看出这就是类型名称，而且是没有::type
};

//当编译器在Widget的模板中看到MyAllocList<T>::type（使用typedef的版本），
//它不能确定那是一个类型的名称。因为可能存在一个MyAllocList的它们没见到的特化版本，
//那个版本的MyAllocList<T>::type指代了一种不是类型的东西。
//MyAllocList<T>::type 是否指的是一个类型忠实地依赖于传入的 T 是什么， 这也是编译器坚持要求你在类型前面冠以 typename 的原因
class Wine { … };

template<>                          //当T是Wine
class MyAllocList<Wine> {           //特化MyAllocList
private:  
    enum class WineType             //参见Item10了解  
    { White, Red, Rose };           //"enum class"

    WineType type;                  //在这个类中，type是
    …                               //一个数据成员！
};
```
*依赖类型*，是指一个类型的确定依赖于另外一个类型。依赖类型的概念出现在模板元编程中。在依赖类型的名称之前必须冠以 typename 。
- 模板别名避免了::type后缀，在模板中使用typedef还经常要求使用typename前缀。
- C++14为C++11中的类型特征转换提供了模板别名。使用type traits中的工具可以实现类型转换
```cpp
std::remove_const<T>::type          //C++11: const T → T 
std::remove_const_t<T>              //C++14 等价形式

std::remove_reference<T>::type      //C++11: T&/T&& → T 
std::remove_reference_t<T>          //C++14 等价形式

std::add_lvalue_reference<T>::type  //C++11: T → T& 
std::add_lvalue_reference_t<T>      //C++14 等价形式

```

**Effective Modern C++ 10**
优先考虑限域enum而非未限域enum
- C++98的enum即非限域enum。
```cpp
// 未限域enum
enum Color { black, white, red };   //black, white, red在Color所在的作用域
auto white = false;                 //错误! white早已在这个作用域中声明

// 限域enum，限域enum是通过“enum class”声明
enum class Color { black, white, red }; //black, white, red限制在Color域内
auto white = false;                     //没问题，域内没有其他“white”
Color c = white;                        //错误，域中没有枚举名叫white
Color c = Color::white;                 //没问题
auto c = Color::white;                  //也没问题（也符合Item5的建议）
```
- 限域enum的枚举名仅在enum内可见。要转换为其它类型只能使用cast。未限域enum则会被隐式转换成整型或浮点数。
```cpp
enum class Color { black, white, red }; //Color现在是限域enum
Color c = Color::red;                   //和之前一样，只是了一个域修饰符
// if (c < 14.5) {                         //错误！不能比较Color和double
//     auto factors =  primeFactors(c);    //错误！不能向参数为std::size_t的函数传递Color参数
// }
if (static_cast<double>(c) < 14.5) {    //奇怪的代码，但是有效
    auto factors = primeFactors(static_cast<std::size_t>(c)); //有问题，但是能通过编译
}
```
- 非限域/限域enum都支持底层类型说明语法，限域enum底层类型默认是int。非限域enum没有默认底层类型。
- 限域enum总是可以前置声明。非限域enum仅当指定它们的底层类型时才能前置。
```cpp
enum class Status;                  //底层类型是int
enum class Status: std::uint32_t;   //Status的底层类型是std::uint32_t（需要包含 <cstdint>）
enum Color: std::uint8_t;   //非限域enum前向声明底层类型为std::uint8_t

```
- 存在一些情况，更适合使用非限域enum。如下,非限域版本相对简洁。
```cpp
using UserInfo =                //类型别名，参见Item9
    std::tuple<std::string,     //名字
               std::string,     //email地址
               std::size_t> ;   //声望

enum UserInfoFields { uiName, uiEmail, uiReputation };
UserInfo uInfo;                         //同之前一样
auto val = std::get<uiEmail>(uInfo);    //啊，获取用户email字段的值

enum class UserInfoFields { uiName, uiEmail, uiReputation };
UserInfo uInfo;                         //同之前一样
auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo);
```

**Effective Modern C++ 13**
- 优先考虑const_iterator而非iterator
STL const_iterator等价于指向常量的指针（pointer-to-const）。它们都指向不能被修改的值。标准实践是能加上const就加上，这也指示我们需要一个迭代器时只要没必要修改迭代器指向的值，就应当使用const_iterator。
```cpp
std::vector<int> values;                                //和之前一样
auto it = std::find(values.cbegin(), values.cend(), 1983);//使用cend，cbegin。返回const_iterator。
values.insert(it, 1998);
```
- 在最大程度通用的代码中，优先考虑非成员函数版本的begin，end，rbegin等，而非同名成员函数。（这个不太重要）

**Effective Modern C++ 15**
constexpr使得在编译期进行复杂计算变得更加方便。
- constexpr对象是const，它被在编译期可知的值初始化
简而言之，所有constexpr对象都是const，但不是所有const对象都是constexpr。如果你想编译器保证一个变量有一个值，这个值可以放到那些需要编译期常量（compile-time constants）的上下文的地方，你需要的是constexpr而不是const。
```cpp
int sz;                             //non-constexpr变量
constexpr auto arraySize1 = sz;     //错误！sz的值在编译期不可知
std::array<int, sz> data1;          //错误！一样的问题
constexpr auto arraySize2 = 10;     //没问题，10是编译期可知常量
std::array<int, arraySize2> data2;  //没问题, arraySize2是constexpr
//注意const不提供constexpr所能保证之事，因为const对象不需要在编译期初始化它的值。
int sz;                            //和之前一样
const auto arraySize = sz;         //没问题，arraySize是sz的const复制
std::array<int, arraySize> data;   //错误，arraySize值在编译期不可知

```
- 当传递编译期可知的值时，constexpr函数可以产出编译期可知的结果。当传递运行期可知的值，constexpr则在运行时产生结果。
```cpp
constexpr                                   //pow是绝不抛异常的constexpr函数
int pow(int base, int exp) noexcept         //C++ 14函数定义可以写多行，C++ 11只能写一行。
{
    auto result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}
constexpr auto numConds = 5;                //（上面例子中）条件的个数
std::array<int, pow(3, numConds)> results;  //结果有3^numConds个元素,编译期计算

auto base = readFromDB("base");     //运行时获取这些值
auto exp = readFromDB("exponent"); 
auto baseToExp = pow(base, exp);    //运行时调用pow函数
```

- constexpr对象和函数可以使用的范围比non-constexpr对象和函数要大
本条款的建议是尽可能的使用constexpr，现在我希望大家已经明白缘由：constexpr对象和constexpr函数可以使用的范围比non-constexpr对象和函数大得多。使用constexpr关键字可以最大化你的对象和函数可以使用的场景。
- constexpr是对象和函数接口的一部分
还有个重要的需要注意的是constexpr是对象和函数接口的一部分。加上constexpr相当于宣称“我能被用在C++要求常量表达式的地方”。如果你声明一个对象或者函数是constexpr，客户端程序员就可能会在那些场景中使用它。如果你后面认为使用constexpr是一个错误并想移除它，你可能造成大量客户端代码不能编译。“尽可能”的使用constexpr表示你需要长期坚持对某个对象或者函数施加这种限制。


##### 高效率相关

**More Effective C++ 16**
优化程序不要盲目优化，现有profile工具找到软件瓶颈，然后优化之，这样才能将优化的工作体现到最后软件的表现上。一定要找到瓶颈再去优化！！否则，在原本不是瓶颈的地方优化，软件行为并不会有多大的改善。

**More Effective C++ 17**
通过惰性计算提升性能
四个例子展示了 lazy evaluation 在各个领域都是有用的：能避免不需要的对象拷贝，通过使用 operator[]区分出读操作，避免不需要的数据库读取操作，避免不需要的数字操作。但是它并不总是有用。就好象如果你的父母总是来检查你的房间，那么拖延整理房间将不会减少你的工作量。实际上，如果你的计算都是重要的，lazy evaluation 可能会减慢速度并增加内存的使用，因为除了进行所有的计算以外， 你还必须维护数据结构让 lazyevaluation 尽可能地在第一时间运行。在某些情况下要求软件进行原来可以避免的计算，这时 lazy evaluation 才是有用的。

**More Effective C++ 18**
通过提前计算提升性能。分期摊还期望的计算。over-eager。
第一种方法cache
比如一个集合提供max() min()的函数，这个函数会被频繁调用。那么可以在每次集合变动的时候提前把这些值算好存储起来，每次调用就直接返回值，省得重新计算。如果此处用惰性求值则是等到调用者真正调用的时候才进行计算，则调用方等待的时间肯定要长一些，同时每次都要计算，也消耗了更多资源。
第二种方法Prefetch
Prefetching(预提取)是另一种方法。你
可以把 prefech 想象成购买大批商品而获得的折扣。例如磁盘控制器从磁盘读取数据时，它们会读取一整块或整个扇区的数据，即使程序仅需要一小块数据。这是因为一次读取一大块数据比在不同时间读取两个或三个小块数据要快。而且经验显示如果需要一个地方的数据，则很可能也需要它旁边的数据。这是位置相关现象。正因为这种现象，系统设计者才有理由为指令和数据使用磁盘 cache 和内存 cache，还有使用指令 prefetch。
还有就是动态数据结构比如hash map扩容，由于扩容开销很大所以它每次扩容的时候，会额外多申请一些空间，来满足未来一段时间的空间需求。

**More Effective C++ 19**
理解临时对象的来源
综上所述，临时对象是有开销的，所以你应该尽可能地去除它们，然而更重要的是训练自己寻找可能建立临时对象的地方。在任何时候只要见到常量引用（reference-to-const）参数和by value参数，就存在建立临时对象而绑定在参数上的可能性。在任何时候只要见到函数返回对象，就会有一个临时对象被建立（以后被释放）。学会寻找这些对象构造，你就能显著地增强透过编译器表面动作而看到其背后开销的能力。
然而概念和现实之间又一个黑暗地带，叫做优化，有时你能以某种方法编写返回对象的函数，以允许你的编译器优化临时对象。这些优化中，最常见和最有效的是返回值优化，这是条款 M20的内容。

**More Effective C++ 20**
返回值优化，C++编译器可以RVO。这里由于return 语句上是一个构造函数，这个技巧叫constructor argument。可以使得C++编译器进行RVO优化，没有临时变量的构造和析构开销，而是直接在c内存下创建了对象。
此外将函数声明为inline，可以节省调用operator *的开销。
```cpp
inline const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.numerator() * rhs.numerator(),lhs.denominator() * rhs.denominator());
}
```
Ratinal c = a * b;

**More Effective C++ 21**
通过重载避免隐式类型转换，可以提高效率。
```cpp
const UPInt operator+(const UPInt& lhs, const UPInt& rhs); // and UPInt

const UPInt operator+(const UPInt& lhs, int rhs); // and int

UPInt upi1, upi2;
...
UPInt upi3 = upi1 + upi2; // 正确,没有由 upi1 或 upi2生成的临时对象
upi3 = upi1 + 10; // 正确, 没有由 upi1 or 10 生成的临时对象
upi3 = 10 + upi2; //10 or upi2 生成的临时对象。这个开销较大。因为10需要转换成UPInt，调用const UPInt operator+(const UPInt& lhs, const UPInt& rhs); 
```

**More Effective C++ 22**
考虑用运算符的赋值形式(op=)取代其单独形式(op)
这里谈论的命名对象、未命名对象和编译优化是很有趣的， 但是主要的一点是 operator
的赋值形式（operator+=）比单独形式(operator+)效率更高。做为一个库程序设计者，应
该两者都提供，做为一个应用程序的开发者， 在优先考虑性能时你应该考虑考虑用 operator
赋值形式代替单独形式。
在这个例子里，从零开始实现 operator+=和-=，而 operator+ 和 operator- 则是通过
调用前述的函数来提供自己的功能。使用这种设计方法，只用维护 operator 的赋值形式就
行了。而且如果假设 operator 赋值形式在类的 public 接口里，这就不用让 operator 的单
独形式成为类的友元
```cpp
class Rational {
public:
...
Rational& operator+=(const Rational& rhs);
Rational& operator-=(const Rational& rhs);
};

const Rational operator+(const Rational& lhs,const Rational& rhs){
return Rational(lhs) += rhs;
}
// operator- 根据 operator -= 来实现
const Rational operator-(const Rational& lhs,const Rational& rhs)
{
return Rational(lhs) -= rhs;
}
```
在这里值得指出的是三个效率方面的问题。
第一、总的来说 operator 的赋值形式比其
单独形式效率更高，因为单独形式要返回一个新对象，从而在临时对象的构造和释放上有一
些开销（参见条款 M19 和条款 M20，还有 Effective C++条款 23）。operator 的赋值形式把
结果写到左边的参数里，因此不需要生成临时对象来容纳 operator 的返回值。
第二、提供 operator 的赋值形式的同时也要提供其标准形式，允许类的客户端在便利与效率上做出折衷选择。
```cpp
//前者比较容易编写、debug 和维护，并且在 80％的时间里它的性能是可以被接受的（参见条款 M16）。后者具有更高的效率
//写法1
result = a + b + c + d;// 可能用了 3 个临时对象每个 operator+ 调用使用 1 个
//写法2
result = a; //不用临时对象
result += b; //不用临时对象
result += c; //不用临时对象
result += d; //不用临时对象
```
下一个例子
第二个模板包含一个命名对象，result。这个命名对象意味着不能在 operator+ 里使用返回值优化（参见
条款 M20）。第一种实现方法总可以使用返回值优化，所以编译器为其生成优化代码的可能
就会更大。
```cpp
template<class T>
const T operator+(const T& lhs, const T& rhs)
{ return T(lhs) += rhs; }

template<class T>
const T operator+(const T& lhs, const T& rhs)
{
T result(lhs); // 拷贝 lhs 到 result 中
return result += rhs; // rhs 与它相加并返回结果
}
```

**More Effective C++ 23**
优化程序运行效率的另一个可以考虑的点，是更换使用的程序库。每个程序库的实现差异很大，更换程序库可以提升代码效率。

##### 技巧和模式
这里介绍了使用传统C++语法，实现一些高级设计目标。值得反复品味。
**More Effective C++ 25**
将构造函数和非成员函数虚拟化。可是实现一些单纯地重写函数(成员，非成员)难以实现的操作。
虚拟构造函数是指能够根据输入给它的数据的不同而建立不同类型的对象。虚拟构造函数在很多场合下都有用处，从磁盘（或者通过网络连接，或者从磁带机上）读取对象信息只是其中的一个应用。 
readComponent就是虚拟构造函数。
```cpp
class NewsLetter {
public:
...
private:
// 为建立下一个 NLComponent 对象从 str 读取数据,
// 建立 component 并返回一个指针。
static NLComponent * readComponent(istream& str);
...
};
NewsLetter::NewsLetter(istream& str)
{
while (str) {
// 把 readComponent 返回的指针添加到 components 链表的最后，
// "push_back" 一个链表的成员函数，用来在链表最后进行插入操作。
components.push_back(readComponent(str));
}
}
```
虚拟拷贝构造函数的名字一般都是 copySelf，cloneSelf 或者是象下面这样就叫做 clone。类的虚拟拷贝构造函数只是调用它们真正的拷贝构造函数。在 NLComponent 中的虚拟拷贝构造函数能让实现 NewLetter 的(正常的)拷贝构造函数变得很容易：
```cpp
class NewsLetter {
	public:
		NewsLetter(const NewsLetter& rhs);
		...
	private:
		list<NLComponent*> components;
};
NewsLetter::NewsLetter(const NewsLetter& rhs)
{
	// 遍历整个 rhs 链表，使用每个元素的虚拟拷贝构造函数
	// 把元素拷贝进这个对象的 component 链表。
	// 有关下面代码如何运行的详细情况，请参见条款 M35.
	for (list<NLComponent*>::const_iterator it = rhs.components.begin(); it != rhs.components.end(); ++it) {
		// "it" 指向 rhs.components 的当前元素，调用元素的 clone 函数，
		// 得到该元素的一个拷贝，并把该拷贝放到
		// 这个对象的 component 链表的尾端。
		components.push_back((*it)->clone());
	}
}
```
具有虚拟行为的非成员函数很简单。你编写一个虚拟函数来完成工作，然后再写一个非虚拟函数，它什么也不做只是调用这个虚拟函数。为了避免这个句法花招引起函数调用开销，你当然可以内联这个非虚拟函数。
```cpp
class NLComponent {
public:
virtual ostream& print(ostream& s) const = 0;
...
};
class TextBlock: public NLComponent {
public:
virtual ostream& print(ostream& s) const;
...
};
class Graphic: public NLComponent {
public:
virtual ostream& print(ostream& s) const;
...
};
inline ostream& operator<<(ostream& s, const NLComponent& c)
{
return c.print(s);
}
```

**More Effective C++ 26**
这里介绍如何限制某个类所能产生的对象数量。
这里讲了用c++实现单例模式，主要依靠局部static变量。使用计数器可以实现更灵活的单个实例的限制，详见“允许对象来去自由”。
限制数量大于1的时候，比如限制5。那么可以设置一个私有计数器，构造函数中+1，析构函数中-1.每次构造函数被调用时都检查一下是否达到上限，达到则抛出异常或返回空指针。同时为了防止计数混乱，可以将构造函数声明为private。这样类就无法被继承，也无法作为其他类的成员变量。
介绍了如何禁止一个类被继承，参考FSA示例。
我们很容易地能够编写一个具有实例计数功能的基类， 然后让像 Printer 这样的类从该基类继承，而且我们能做得更好。

```cpp
template<class BeingCounted>
class Counted {
	public:
		class TooManyObjects{}; // 用来抛出异常
		static int objectCount() { return numObjects; }
	protected:
		Counted();
		Counted(const Counted& rhs);
		~Counted() { --numObjects; }
	private:
		static int numObjects;
		static const size_t maxObjects;
		void init(); // 避免构造函数的
}; // 代码重复
template<class BeingCounted> Counted<BeingCounted>::Counted() { init(); }
template<class BeingCounted> Counted<BeingCounted>::Counted(const Counted<BeingCounted>&) { init(); }
template<class BeingCounted> void Counted<BeingCounted>::init(){
if (numObjects >= maxObjects) throw TooManyObjects();
++numObjects;
}
```
从这个模板生成的类仅仅能被做为基类使用，因此构造函数和析构函数被声明为protected。注意 private 成员函数 init 用来避免两个 Counted 构造函数的语句重复。
现在我们能修改 Printer 类，这样使用 Counted 模板.
Printer 使用了 Counter 模板来跟踪存在多少 Printer 对象，坦率地说，除了 Printer的编写者，没有人关心这个事实。它的实现细节最好是 private，这就是为什么这里使用private继承的原因 
```cpp
class Printer: private Counted<Printer> {
public:
	// 伪构造函数
	static Printer * makePrinter();
	static Printer * makePrinter(const Printer& rhs);
	~Printer();
	void submitJob(const PrintJob& job);
	void reset();
	void performSelfTest();
	...
	using Counted<Printer>::objectCount; // 这样使得外部调用者可以访问到objectCount()函数
	using Counted<Printer>::TooManyObjects; // 由于这个异常抛出后，对于客户是可见的，所以需要声明出来，对客户可见。
private:
	Printer();
	Printer(const Printer& rhs);
};
```
当 Printer 继承 Counted<Printer>时，它可以忘记有关对象计数的事情。编写 Printer 类时根本不用考虑对象计数，就好像有其他人会为它计数一样。Printer 的构造函数可以是这样的：
```cpp
Printer::Printer()
{
进行正常的构造函数运行
}
```

**More Effective C++ 27**
要求或禁止在堆中产生对象
*这个内容后面有时间慢慢看，或者需要的时候再来看*

**More Effective C++ 28**
smart指针。这节不用看了。Effective Modern C++已经有了对smart指针更全面的叙述。

**More Effective C++ 29**
*这个内容后面有时间慢慢看，或者需要的时候再来看*
引用计数。
使用引用计数有两个动机：第一个是简化跟踪堆中的对象的过程，这个shared_ptr可以做到；第二个是第二个动机是由于一个简单的常识。如果很多对象有相同的值，将这个值存储多次是很无聊的。更好的办法是让所有的对象共享这个值的实现，这个就是std::string的实现方式。
评述
实现引用计数不是没有代价的。每个被引用的值带一个引用计数，其大部分操作都需要以某种形式检查或操作引用计数。对象的值需要更多的内存，而我们在处理它们时需要执行更多的代码。此外，就内部的源代码而言，带引用计数的类的复杂度比不带的版本高。没有引用计数的 String 类只依赖于自己，而我们最终的 String 类如果没有三个辅助类（StringValue、RCObject 和 RCPtr）就无法使用。确实，我们这个更复杂的设计确保在值可共享时的更高的效率；免除了跟踪对象所有权的需要，提高了引用计数的想法和实现的可重用性。但，这四个类必须写出来、被测试、文档化、和被维护，比单个类要多做更多的工作。即使是管理人员也能看出这点。
引用计数是基于对象通常共享相同的值的假设的优化技巧（参见 Item M18）。如果假设不成立的话，引用计数将比通常的方法使用更多的内存和执行更多的代码。另一方面，如果你的对象确实有具体相同值的趋势，那么引用计数将同时节省时间和空间。共享的值所占内存越大，同时共享的对象数目越多，节省的内存也就越大。创建和销毁这个值的代价越大，你节省的时间也越多。总之，引用计数在下列情况下对提高效率很有用：
少量的值被大量的对象共享。这样的共享通常通过调用赋值操作和拷贝构造而发生。对象/值的比例越高，越是适宜使用引用计数。对象的值的创建和销毁代价很高昂，或它们占用大量的内存。即使这样，如果不是多个对象共享相同的值，引用计数仍然帮不了你任何东西。只有一个方法来确认这些条件是否满足，而这个方法不是猜测或依赖直觉（见 ItemM16）。这个方法是使用 profiler 或其它工具来分析。使用这种方法，你可以发现是否创建和销毁值的行为是性能瓶颈，并能得出对象/值的比例。只有当你手里有了这些数据，你才能得出是否从引用计数上得到的好处超过其缺点。即使上面的条件满足了，使用引用计数仍然可能是不合适的。有些数据结构（如有向图）将导致自我引用或环状结构。这样的数据结构可能导致孤立的自引用对象，它没有被别人使用，而其引用计数又绝不会降到零。因为这个无用的结构中的每个对象被同结构中的至少一个对象所引用。商用化的垃圾收集体系使用特别的技术来查找这样的结构并消除它们但我们现在使用的这个简单的引用计数技术不是那么容易扩充出这个功能的。
即使效率不是主要问题，引用计数仍然很吸引人。如果你不放心谁应该去执行删除动作，那么引用计数正是这种让你放下担子的技巧。很多程序员只因为这个原因就使用引用计数。
让我们用最后一个问题结束讨论。当 RCObject::removeReference 减少对象的引用计数时，它检查新值是否为 0。如果是，removeReference 通过调用 delete this 销毁对象。这个操作只在对象是通过调用 new 生成时才安全，所以我们需要一些方法以确保 RCObject只能用这种方法产生。
此处，我们用习惯方法来解决。RCObject 被设计为只作被引用计数的值对象的基类使用，而这些值对象应该只通过灵巧指针 RCPtr 引用。此外，值对象应该只能由值会共享的对象来实例化；它们不能被按通常的方法使用。在我们的例子中，值对象的类是 StringValue，我们通过将它申明为 String 的私有而限制其使用。 只有 String 可以创建 StringValue 对象，所以 String 类的作者应该确保这些值对象都是通过 new 操作产成的。
于是，我们限制 RCObject 只能在堆上创建的方法就是指定一组满足这个要求的类，并确保只有这些类能创建 RCObject 对象。用户不可能无意地（或有意地）用一种不恰当的方法创建 RCObject 对象。我们限制了创建被引用计数对象的权力，当我们交出这个权力时，必须明确其附带条件是满足创建对象的限制条件

**More Effective C++ 30**
代理类。
这里介绍了如何通过代理类实现二维数组。每个 Array1D 对象扮演的是一个一维数组，而这个一维数组没有在使用 Array2D 的程序中出现。扮演其它对象的对象通常被称为代理类。在这个例子里，Array1D 是一个代理类。它的实例扮演的是一个在概念上不存在的一维数组。 （术语代理对象（proxy object）和代理类（proxy classs）还不是很通用；这样的对象有时被叫做 surrogate。 ）
Proxy 类可以完成一些其它方法很难甚至不可能实现的行为。多维数组是一个例子，左/右值的区分是第二个，限制隐式类型转换（见 Item M5）是第三个。
同时，proxy 类也有缺点。作为函数返回值，proxy 对象是临时对象（见 Item 19），它们必须被构造和析构。这不是免费的，虽然此付出能从具备了区分读写的能力上得到更多的
补偿。Proxy 对象的存在增加了软件的复杂度，因为额外增加的类使得事情更难设计、实现、理解和维护。
最后，从一个处理实际对象的类改换到处理 proxy 对象的类经常改变了类的语义，因为 proxy 对象通常表现出的行为与实际对象有些微妙的区别。有时，这使得在设计系统时无法选择使用 proxy 对象，但很多情况下很少有操作需要将 proxy 对象暴露给用户。例如，很少有用户取上面的二维数组例子中的 Array1D 对象的地址，也不怎么有可能将下标索引的对象（见 Item M5）作参数传给一个期望其它类型的函数。在很多情况下，proxy 对象可以完美替代实际对象。当它们可以工作时，通常也是没有其它方法可采用的情况。

```cpp
template<class T>
class Array2D {
	public:
	class Array1D {
	public:
	T& operator[](int index);
	const T& operator[](int index) const;
	...
	};
	Array1D operator[](int index);
	const Array1D operator[](int index) const;
	...
};
```
如何通过代理类区分[]是读操作还是写操作,使用CharProxy代理char。
```cpp
class String { // reference-counted strings;
	public: // see Item 29 for details
		class CharProxy { // proxies for string chars
			public:
				CharProxy(String& str, int index); // creation
				CharProxy& operator=(const CharProxy& rhs); // lvalue
				CharProxy& operator=(char c); // uses
				operator char() const; // rvalue use, 因为这个函数返回了一个字符的值，并且又因为 C++限定这样通过值返回的对象只能作右值使用，所以这个转换函数只能出现在右值的位置。
				char * operator&();
				const char * operator&() const;
				private:
				String& theString; // string this proxy pertains to char within that string this proxy stands for
				int charIndex; 
		};
		// continuation of String class
		const CharProxy operator[](int index) const; // for const Strings
		CharProxy operator[](int index); // for non-const Strings
		...
		friend class CharProxy;
	private:
		RCPtr<StringValue> value;
};
const String::CharProxy String::operator[](int index) const
{
	return CharProxy(const_cast<String&>(*this), index);
}
String::CharProxy String::operator[](int index)
{
	return CharProxy(*this, index);
}
String::CharProxy::CharProxy(String& str, int index) : theString(str), charIndex(index) {}
String::CharProxy::operator char() const { return theString.value->data[charIndex]; }
String::CharProxy& String::CharProxy::operator=(const CharProxy& rhs)
{
	// if the string is sharing a value with other String objects,
	// break off a separate copy of the value for this string only
	if (theString.value->isShared()) {
		theString.value = new StringValue(theString.value->data);
	}
	// now make the assignment: assign the value of the char
	// represented by rhs to the char represented by *this
	theString.value->data[charIndex] =
	rhs.theString.value->data[rhs.charIndex];
	return *this;
}
String::CharProxy& String::CharProxy::operator=(char c)
{
	if (theString.value->isShared()) {
		theString.value = new StringValue(theString.value->data);
	}
	theString.value->data[charIndex] = c;
	return *this;
}
const char * String::CharProxy::operator&() const
{
	return &(theString.value->data[charIndex]);
}
char * String::CharProxy::operator&()
{
	// make sure the character to which this function returns
	// a pointer isn't shared by any other String objects
	if (theString.value->isShared()) {
	theString.value = new StringValue(theString.value->data);
	}
	// we don't know how long the pointer this function
	// returns will be kept by clients, so the StringValue
	// object can never be shared
	theString.value->markUnshareable();
	return &(theString.value->data[charIndex]);
}
```

**More Effective C++ 31**
让函数根据一个以上的对象来决定怎么虚拟。
碰撞函数processCollision()，需要实现为虚函数，根据object1的动态类型和object2的动态类型决定，具体调用什么函数。
```cpp
class GameObject { ... };
class SpaceShip: public GameObject { ... };
class SpaceStation: public GameObject { ... };
class Asteroid: public GameObject { ... };
void checkForCollision(GameObject& object1,GameObject& object2){
	if (theyJustCollided(object1, object2)) {
	processCollision(object1, object2);
	}
	else {
	...
	}
}
一种方法是用虚函数加 RTTI(RTTI是”Runtime Type Information”的缩写，意思是运行时类型信息，它提供了运行时确定对象类型的方法。)。
一种方法只使用虚函数。
一种方法是模拟虚函数表。
使用非成员的碰撞处理函数。
```


##### 哪些情况使用inline
**Effective C++ 30**
将大多数inlining限制在小型、被频繁调用的函数身上。这可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，是使程序的速度提升机会最大化。
不要只因为function templates出现在头文件，就将他们声明为inline。


##### 哪些情况使用const
**Effective C++ 3**
应该尽可能地使用const，将某些东西声明为const可帮助编译器侦测出错误用法。const 可被施加于任何作用域的对象、函数参数、函数返回类型、成员函数本体。
当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复。
编译器强制实施bitwise constness,但你编写程序时应该使用“概念上的常量性”conceptual constness，也就是是说函数是否能被标记为const，不只看是否改变了成员变量，还要看给外部调用者提供了改变成员变量的机会，如果一个函数返回了内部成员变量的指针，那么它不应该是const。我们写const函数应该按照conceptual constness来写，就是逻辑上对调用者保持是不变的。这个时候const函数内部是可以修改部分变量的，但是这些变量需要使用mutable来修饰。如下：
```cpp
class CTextBlock{
	public:
	...
	std::size_t length() const;
	private:
	char* pText;
	mutable std::size_t textLength;
	mutable bool lengthIsValid;
};
std::size_t CTextBlock::length() const
{
	if(!lengthIsValid){
		textLength = std::strlen(pText);
		lengthIsValid = true;
	}
	return textLength;
}
```

##### 哪些情况下使用friend
STL中迭代器就是容器的友元。
单元测试函数可以作为对应的类的友元。
重载操作符,如下：
```cpp
class person{
public:
//作为类的成员函数，重载运算符参数只需要右操作值即可
   friend bool operator<(const Person& arg1, const Person& arg2);
private:
   int a;
};

//实现时不需要类名限定
bool operator<(const Person& arg1, const Person& arg2){
    if( arg1.a < arg2.a)
       return true;
    else
        return false;
}
person a1,a2;
bool bRet = a1 < a2 ; 
```
##### 关于定制new和delete
**Effective C++ 49**
new-handler的行为
set_new_handler允许客户指定一个函数，在内存分配无法获得满足时被调用。
Nothrow new是一个颇为局限的工具，因为它只适用于内存分配；后继的构造函数调用还是可能抛出异常。
一个设计良好的new-handler必须做以下事情：
- 让更多内存可被使用
- 安装另一个new-handler
- 卸除new-handler
- 抛出bad_alloc 的异常
- 不返回

**Effective C++ 50**
了解new和delete的合理替换时机
三个常见的理由：
- 用来检测运用上的错误。overruns写入点在分配区尾端之后和underruns写入点在分配区起点之前。比如new分配额外空间存放签名，delete的时候检查签名是否存在，就可以验证该区域是否被错误覆盖了其他信息。
- 为了强化效能。定制new和delete可以满足特定场景下提升内存管理效率，因为默认的new和delete为来满足各种使用场景，它的效率不是特别高。
- 为了收集使用上的统计数据。定制new和delete可以收集程序使用内存行为的统计信息。
还有其他理由：
- 为了增加分配和归还的速度
- 为了降低缺省内存管理器带来的空间额外开销。
- 为了弥补缺省分配器中的非最佳齐位。
- 为了将相关对象成簇几种。
- 为了获得非传统的行为。

**Effective C++ 51**
编写时需固守常规
operator new 应该内含一个无穷循环，并在其中尝试分配内存，如果它无法满足内存需求，就该调用new-handler。它也应该有能力处理0 bytes申请。Class专属版本则还应该处理“比正确大小更大的(错误)申请”。
operator delete应该在收到null指针时不做任何事。Class专属版本则还应该处理“比正确大小更大的（错误）申请”。

**Effective C++ 52**
1. 当你写一个placement operator new, 请确定也写出了对应的placement operator delete。如果没有这样做，你的程序可能会发生隐微而时断时续的内存泄露
2. 当你声明placement new和placement delete， 请确定不要无意识地遮掩了他们的正常版本。



#### 类的成员函数
如果成员函数定义发生在头文件，那么这个头文件中此函数很可能被优化成inline(如果成员函数的size不是太大的话)。
因为有这个特性，才使得类中的函数定义可以发生在头文件中。如果是在头文件的类外定义函数，那么编译器会由于定义了相同符号报警。
一般情况不鼓励在头文件中完成函数定义，除非是希望类中的成员函数成为inline。

#### C++特殊成员函数
C++编译器默认生成8个成员函数，Effective C++和Effective Modern C++中都没有提到取地址操作符相关的两个函数。
```cpp
/**
 * 在c++中，一个类有八个默认函数
 * 1、默认构造函数
 * 2、默认拷贝构造函数
 * 3、默认析构函数
 * 4、默认重载赋值运算符函数
 * 5、默认重载取址运算符函数
 * 6、默认重载取址运算符函数const函数
 * 7、默认移动构造函数（c++11）
 * 8、默认重载移动赋值操作符函数（c++11）
 * 下面的实例重新定义了默认成员函数，让大家认清编译器自动生成的成员函数内部的主要逻辑。
 */
class A {
public:
	//默认构造函数
	A() { std::cout << "默认构造函数" <<" this address: " << this << std::endl; }
	//默认拷贝构造函数
	A(const A&) { std::cout << "默认拷贝构造函数" << " this address: " << this << std::endl; }
	//默认析构函数
	~A() { std::cout << "默认析构函数" << " this address: " << this << std::endl; }
	//默认重载赋值运算符函数
	A& operator= (const A& a) { 
          if(this == &a) {
            return *this;
          }
	  std::cout << "默认重载赋值运算符函数" << "this address: " << this << std::endl;
	  return *this; 
	}
	//默认重载取址运算符函数
	A* operator& () {
	  std::cout << "默认重载取址运算符函数" << "this address: " << this << std::endl; 
          return this;
    }
	//默认重载取址运算符const函数
	A const* operator& () const {
	  std::cout << "默认重载取址运算符const函数" <<" this address: " << this << std::endl; 
          return this;
	}
	//默认移动构造函数
	A(A&&) { std::cout << "默认移动构造函数" <<" this address: " << this << std::endl; }
	//默认重载移动赋值操作符
	A& operator= (const A&& a) { 
	  if(this == &a) {
	    return *this;
	  }
	  std::cout << "默认移动构造函数" <<" this address: " << this << std::endl; 
	  return *this;
	}
};
/**
 * 1. 子类的构造函数：必须调用父类的构造函数去完成子类中父类那部分成员的初始化。如果父类没有默认的构造函数，则必须在子类构造函数的初始化列表阶段显示调用。
 * 2. 子类的拷贝构造函数： 必须调用父类的拷贝构造函数去完成子类中父类那部分成员的拷贝初始化。
 * 3. 子类的拷贝赋值重载： 必须调用父类的operator=去完成子类中父类那部分成员的复制。
 * 4. 子类的析构函数： 无需调用父类，系统会自动调用父类的析构函数完成自己空间的清理。
 * 5. 子类的移动构造函数： 必须调用父类的移动构造函数去完成子类中父类那部分成员的移动初始化。
 * 6. 子类的移动赋值重载： 必须调用父类的operator=去完成子类中父类那部分成员的移动赋值。
 * 7. 子类的载取址运算符函数：直接返回this指针。
 * 8. 默认重载取址运算符const函数：直接返回this指针。
 */
class Person {                          //父类
public:
	Person(const char* name = "ly")    //构造,最好写成全缺省，方便子类直接调用
		:_name(name){
		cout << "Person()"<< endl;
	}
	Person(const Person& p)     //拷贝构造
		:_name(p._name){
		cout << "Person(const Person& p)" << endl;
	}
	Person& operator =(const Person&p) {   //赋值重载
		cout << "Person& operator =(const Person&p)" << endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}
	~Person(){                 //析构
		cout << "~Person()" << endl;
	}       
protected:
	string _name;
};

class Student :public Person {       //子类
public:
	Student(const char* name, int num)    //构造
		:Person(name)  //子类不能自己初始化父类成员，即不能用_name("ly")初始化 
		, _num(num) {
		cout << "Student(const char* name, int num)" << endl;
	}
	Student(const Student&s)     //拷贝构造
		: Person(s)       //切片完成拷贝构造
		, _num(s._num) {
		cout << "Student(const Student&s) " << endl;
	}
	Student &operator=(const Student &s) {   //赋值重载
		cout << "Student &operator=(const Student &s)" << endl;
		if (this != &s)
		{
			Person::operator=(s);    //父类operator=和子类函数会构成隐藏，所以必须指明作用域
			_num = s._num;
		}
		return *this;
	}
	~Student() {        //析构
		cout << "~Student() " << endl;   //父类空间编译器负责清理
	}
protected:
	int _num;
};
```
1. **Effective C++ 5**
C++编译器默认生成下面6个成员函数：
   DefaultConstructor
   CopyConstructor
   MoveConstructor
   CopyAssignment
   MoveAssignment
   Destructor
这些成员函数是public且inline的，且只有这些函数被调用的时候，编译器会为他们生成相应成员函数。
编辑器在一些情况下是不会自动生成成员函数的，具体包含哪些情况，需要详细阅读Effective C++的第5节。

1.1. 默认拷贝构造函数和默认拷贝赋值构造函数在一些情况下无法生成：
https://blog.csdn.net/qq_37026934/article/details/132472391
如果下面任何一个条件为真，则触发copy assignment operator的隐式删除
类T有用户定义的移动构造
类T有用户定义的移动赋值操作
如果下面任何一个条件为真，则将默认copy assignment operato定义为delete
class T有一个数据成员是非static且为const的non-class type
class T有一个数据成员是非静态的引用类型
class T有一个不能被copy-assigned的类型或者class T的基类不能被copy-assigned
class T是一个union类似的class，并且还有多个成员，这些成员对应的assignment operator是non-trivial的

*这个需要搞懂*
1.2. C++中的trivial和non-trivial构造/析构/拷贝/赋值函数及POD类型
https://blog.csdn.net/GoddessNaa/article/details/129393165


2. **Effective C++ 6**
为驳回编译器自动提供的功能，可将相应的成员函数声明为private并且不予实现。使用像Uncopyable这样的base
class也是一种做法。（来自Effective C++的第6节） 使用deleted

3. **Effective Modern C++ 11**
标记成员函数防止自动生成默认的成员函数，是一个更好的办法。并且它也适用于非成员函数和模板实例化(Modern
Effective C++的第11节)

4. **Effective Modern C++ 17**
Generated special member functions are implicitly public and inline, 
and they’re nonvirtual unless the function in question is a destructor 
in a derived class inheriting from a base class with a virtual destructor.
In that case, the compiler-generated destructor for the derived class is also virtual.
使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。(Modern Effective
C++的第17节)

5. **继承体系下的派生类的默认成员函数**
派生类的默认成员函数生成规则，编译器只在没有对应类型成员函数的时候才生成默认成员函数。可能是这个样子
```

```
6. **C++ 生成的默认移动构造函数具备什么行为**
当成员类型有移动构造函数时，会调用该成员的移动构造函数，否则调用默认拷贝构造函数。
结果输出 a.p与b.p地址一样的,而对于a.str显示为空而b.str显示为Fuck.只有string的资源转移了个人理解：C++编译器合成的默认移动函数对于基本类型所谓移动只是把其值拷贝，对于string这类类成员中因为其类实现了移动构造函数才会真正的所谓资源移动。int*看上去是个指针，是个资源，可以被“移动”，但对编译器来说指针就和int一样只是个值，所以只是单纯的复制值而已。比如你移动一个int，并不会让原本的int变成0。
另外只要定义了析构函数,那就不会默认生成移动构造函数,因为对于基本类型来说是"复制"而非真正的移动,只要其一析构了,另外一个的资源也就没了.所以只要定义了析构函数,就不会合成移动构造。
```
class A
{
public:
	int *p = new int;
	string str = "Fuck";
};

int main()
{
	A a;
	A b(std::move(a));
	cout << a.p << " " << a.str << " ";
	cout << b.p << " "<<b.str << " ";
	system("pause");
}
```

7. **C++默认拷贝构造函数**
当类中没有定义拷贝构造函数时，编译器会默认提供一个拷贝构造函数，进行成员变量之间的拷贝。(这个拷贝操作是浅拷贝，拷贝者和被拷贝者若是同一个地址，则为浅拷贝，反之为深拷贝。)

8. **Effective C++ 10**
为了实现连锁赋值，赋值操作符必须返回一个refernce to *this。
```
int x,y,z;
x = y = z = 15;//赋值连锁形式，从右侧逐一完成赋值直到最左侧
```
为了实现连锁赋值，赋值操作符必须返回一个reference指向操作符的左侧实参，也就是返回一个refernce to *this。
```cpp
class Widget{
	public:
	Widget& operator=(const Widget & rhs){
		...
		return *this;
	}
	Widget& operator+=(const Widget & rhs){
		...
		return *this;
	}
}
```

9. **Effective C++ 11**
考虑到使用operator=进行自我赋值时的正确性，需要仔细考虑operator内部的实现。
```cpp
Widget w;
w = w;//需要保证正确
```
- 确保当对象自我赋值时 operator= 有良好行为，其中技术包括比较“来源对象” 和 “目标对象”的地址、精心周到的语句顺序，以及copy-and-swap.
- 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。

10. **Effective C++ 12**
复制对象时勿忘其每一个成分。
默认生成的拷贝构造和拷贝赋值会将对象的所有成员变量做一份拷贝。
当你编写一个copying函数，请确保(1)复制所有local成员变量.(2)调用所有base classes内的适当的copying函数。
不要另copy赋值函数调用copy构造函数，因为这样是在试图构造一个已经存在的对象，但是此对象由于尚未构建完成，调用它的拷贝构造函数会出错。
如果想复用copy构造函数的代码，可以新建一个private函数里面包含共用代码，然后copy构造和copy赋值共同调用这个函数。


*总结*
使用deleted和default明确表名特殊成员函数哪些希望自动生成，哪些不希望生成。
这样可以防止由于默认成员函数的生成规则，在将来我们添加了某个成员函数导致其他默认成员函数不再生成，造成错误。

#### 类的多态


#### 异常
1. **Effective Modern C++ 14**
声明函数为noexcept，如果他们不抛出异常。
大多数程序员认为相比 C++98 异常规范带来的好处，它带来更多的麻烦。
在 C++11 的工作中，出现了一个共识，即关于函数的异常发出行为的真正有意义的信息是它是否有任何异常。
所以C++11 异常规范的基础是声明会发生异常或不会发生异常，它不声明具体异常类型。所以C++中推荐使用noexcept表达无异常，不使用noexcept则表达可能有异常。
所以函数在声明的时候，是否声明它是否为noexcept十分重要，重要性与成员函数是否为const一样。
但是将一个函数声明为noexcept是一个重要决定，它意味着要长期维护保证它的确是no except。
不必将一个可能产生exception的函数，费劲周章改造为no except。因为这样改造往往会丢失掉noexcept本身带来的性能优化，因为代码实现变得复杂。同时调用者在代码逻辑也会变得复杂。
将“noexcept”应用于不会产生异常的函数还有一个额外的动机：它允许编译器生成更好的目标代码。
noexcept可以直接用于函数声明，也可以用于限制函数的参数为noexcept(当参数为函数指针时)，
还可以声明noexcept为条件noexcept，也就是说模板生成的函数是否为noexcept取决于入参对象的swap是否为noexcept，如下：
```cpp
template <class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));
```
in C++11, this style rule has been all but upgraded to a language rule. 
By default, all memory deallocation functions and all destructors—both user-defined and compilergenerated—are implicitly noexcept.
当然也有例外，就是析构函数调用的其他析构函数声明了noexcept(false)。

2. **More Effective C++ 14**
异常规格是一个应被审慎使用的特性。在把它们加入到你的函数之前，应考虑它们所带来的行为是否就是你所希望的行为。
它会由于实际抛出的异常类型与声明的不符，导致程序被except处理，进入到abort而停止程序。激活的栈中的局部变量没有被释放，因为abort在关闭程序是不进行清除操作。

3. **异常会阻止析构函数被调用**
3.1. Linux信号处理机制以及如何触发
https://zhuanlan.zhihu.com/p/410932421

3.2. std::abort
std::abort()是一个C++标准库函数，他会导致程序异常终止。当std::abort()被调用时，程序会立即终止，不会调用自动、线程局部和static storage durations变量的析构函数。也不会调用使用std::atexit()和std::at_quick_exit()注册的函数。
在Linux中，如果程序调用了std::abort(),则会生成一个SIGABRT信号，该信号可以被捕获并处理。可以使用signal()函数来注册一个信号处理程序，以便在程序接收到SIGABRT信号时执行特定的操作。

3.3. std::exit
下文提到的资源包括：线程本地对象、静态变量、C 的文件描述符、std::tmpfile 打开的文件。
- std::_Exit
终止程序，不清理资源。
- std::abort
终止程序，不清理资源。会调用 SIGABRT 信号的处理函数，这个处理函数不会返回。
- std::terminate
std::terminate 调用当前安装的 std::terminate_handler。默认的 std::terminate_handler 调用 std::abort 。
- std::quick_exit
终止程序，清理部分资源。以注册顺序的逆序调用传递给 std::at_quick_exit 的函数。若调用这些函数抛出异常，则调用 std::terminate 。调用所有注册的函数后，调用 std::_Exit(exit_code) 。
不调用传递给 std::atexit 的函数。
- std::exit
终止程序，清理所有资源（不包括栈上的对象）。
清理顺序：
  所有的线程本地变量在静态变量前析构（如果 thread_local 有 static 修饰，依然在这一步析构）。
  静态变量和通过 std::atexit 注册的函数按构造和注册 的顺序逆序析构（因此两者可以穿插进行）。
  关闭所有的 C 文件流。
  移除 std::tempfile。
  https://blog.csdn.net/IWSDAB/article/details/105244349
- return
终止程序，清理全部资源，包括栈上对象。自动析构全局对象、以及函数内定义的局部static对象。

3.4. 何时使用std::exit,std::abort,std::quici_exit?
在 C++ 中，exit() 函数和 EXIT_FAILURE 宏通常一起使用，用于在程序执行过程中遇到错误或异常情况时，立即终止程序并返回一个非零的退出状态码。这样可以让调用程序（如操作系统或其他程序）知道程序执行失败。
exit() 函数是 C++ 标准库 <cstdlib> 中的函数，它用于立即终止程序的执行。它接受一个整数参数，表示程序的退出状态码。exit() 函数被调用时，程序会立即退出，并且向调用程序返回指定的退出状态码。
EXIT_FAILURE 是一个预定义的宏，它通常被定义为一个非零整数（通常为 1）。它用于表示程序执行失败的退出状态码。与之相对应的，C++ 标准库还定义了另一个宏 EXIT_SUCCESS，它表示程序执行成功时的退出状态码，通常定义为 0。
在通常的用法中，exit(EXIT_FAILURE); 表示程序执行失败，而 return 0; 或 exit(EXIT_SUCCESS); 表示程序执行成功。
注意：
exit()是会导致内存泄露的，但是这种内存泄露通常没有不良后果，不需要努力去规避。exit()之后不久进程就终结了，操作系统会把该进程使用的所有内存全部回收。如果一个对象使用了内存之外的其他系统资源，比如建了一个临时文件，又没有利用操作系统的特有功能把它搞成关闭即删除的，而是在析构函数里删除，那么exit以后就会把文件残留在文件系统里。总之，c++里调用exit不是个好习惯。

**More Effective C++ 12**
理解“抛出一个异常”与“传递一个参数”或“调用一个虚函数”间的差异
1. 异常对象在传递是总是被进行拷贝；当通过传值方式捕获时，异常对象被拷贝了两次。对象做为参数传递给函数时不一定需要被拷贝。
2. 对象做为异常被抛出与作为参数传递给函数相比，前者类型转换比后者要少。
3. cactch子句进行异常类型匹配的顺序是他们在源代码中出现的顺序，第一个类型匹配成功的cactch将被用来执行。当一个对象调用一个虚拟函数时，被选择的函数位于与对象类型匹配最佳的类里，即使该类不是在源代码的最前头。

**More Effective C++ 13**
通过引用捕获异常。这是最佳选择。

**More Effective C++ 15**
异常处理是有开销的。尽量避免抛出异常和捕获异常。避免使用异常规格，因为异常规格也是有开销的。

**Google为什么不使用异常**
从表面上看来，使用异常利大于弊, 尤其是在新项目中. 但是对于现有代码, 引入异常会牵连到所有相关代码. 如果新项目允许异常向外扩散, 在跟以前未使用异常的代码整合时也将是个麻烦. 因为 Google 现有的大多数 C++ 代码都没有异常处理, 引入带有异常处理的新代码相当困难.
这里是来自网友的讨论：https://www.zhihu.com/question/31614576/answer/95492773

*总结*
c++代码中只有两种类型的函数：不抛异常和可能抛出异常两种。使用noexcept标记。
为明确保证今后都不抛出异常的函数添加noexcept，其他情况不需要添加noexcept，更不需要使用throw()。
例如：如果一个类的对象只在std::vector中使用，且希望这个类能够在容器中使用到它的move函数，则需要确保move函数noexcept。


#### C++对象的生存周期和存储区
1. **生存周期**
C++（自C++11起）使用四种不同的方案来存储数据，这些方案的区别就在于数据保留在内存中的时间。
1.1. 自动存储： 在函数定义中声明的变量（包括函数参数）的存储持续性为自动的。它们在程序开始执行所属的函数或代码块时被创建，在执行完函数或代码块时，它们使用的内存被释放。C++有两种存储持续性为自动的变量。
1.2. 静态存储： 在函数定义外 被定义的变量 和 使用关键字static 定义的变量。它们在程序整个运行过程中都存在。C++有3种存储持续性为静态的变量。
C++为静态存储持续性变量（静态变量）提供了3种链接性：外部链接性（可在其他文件中访问）、内部链接性（只能在当前文件中访问）和无链接性（只能在当前函数或代码块中访问）。这3种链接性都在整个程序执行期间存在，与自动变量相比，它们的寿命更长。如果没有显示的初始化变量，默认情况下，静态 数组、结构的每个元素或成员都被设置为0.
```cpp
int  global = 100; //static duration，外部链接性,全局作用域
static int in_file = 10;  //static duration， 内部链接性，文件作用域
int main(){
    static int count = 1; // static duration,无链接性，块作用域
    ……
}
```
1.3. 动态存储： 用new运算符分配的内存将一直存在，直到使用delete运算符将其释放或程序结束为止。这种内存的持续性为动态，有时被称为自由存储（free store） 或 堆（heap）。
1.4. 线程存储（C++11）：当前，多核处理器很常见，这些CPU可同时处理多个执行任务。这让程序能够将计算放在可并行处理的不同线程中。如果变量是使用关键字thread_local声明的，则其生命周期与所属的线程一样长。 

2. **存储区**
在C++语言中内存主要分为如下4个存储区：
2.1. 栈(Stack)：位于函数内的局部变量（包括函数实参），由编译器负责分配释放，函数结束，栈变量失效。
2.2. 堆(Heap)：由new申请的内存，且由delete或delete[]负责释放。而C中程序员用malloc/calloc/realloc分配，free释放
2.3. 全局区/静态区(Global Static Area)： 全局变量和静态变量存放区，程序一经编译好，该区域便存在。
        在C++中，由于全局变量和静态变量编译器会给这些变量自动初始化赋值，所以没有区分了初始化变量和未初始化变量了。
        需要说明一点，全局静态变量和局部静态变量都是存储在同一个静态区(全局区)，只是作用域不同。程序结束后才释放空间。     
2.4. 代码+常量存储区： 这是一块比较特殊的存储区，专门存储不能修改的常量(一般是const修饰的变量，或是一些常量字符串)。还存储程序代码。

自由存储区和堆的区别是：
堆是操作系统维护的一块内存，是一个物理概念，而自由存储区是C++中通过new与delete动态分配和释放的对象的存储区，是一个逻辑概念。堆与自由存储区并不等价。
自由存储是 C++ 中通过 new 和 delete 动态分配和释放对象的抽象概念。基本上，所有的 C++ 编译器默认使用堆来实现自由存储。也就是说，默认的全局运算符 new 和 delete 也许会使用 malloc 和free 的方式申请和释放存储空间，这时自由存储区就位于堆上。但程序员也可以通过重载操作符，改用其他内存来实现自由存储，例如全局变量做的对象池，这时自由存储区就不位于堆上了。


#### 构造函数
1. **Effective C++ 4**
初始化成员列表的方式效率较高，应该尽量采用此种方式进行成员变量初始化。列表中成员变量的顺序最好和成员变量声明的顺序保持一致。
对于大多数类型而言，比起先调用default构造函数然后再调用copy assignment操作符，单只调用一次copy构造函数是比较高效的，有时甚至高效得多。
对于内置型对象如numTimesConsulted,其初始化和赋值的成本相同，但为了一致性最好也通过成员初始化列来初始化。
使用初始化成员列表的时候，需要将成员变量都列出来，明确每个变量的构造方式。
https://en.cppreference.com/w/cpp/language/constructor
如果成员变量就地初始化，成员变量又出现在初始化列表中，则就地初始化被忽略，以初始化列表中的为准。

2. **深度探索C++对象模型 2.4节**
初始化成员列表的方式效率较高，应该尽量采用此种方式进行成员变量初始化。
列表中成员变量的顺序最好和成员变量声明的顺序保持一致。
当使用列表中的成员初始化另一个成员，或者需要调用成员函数的时候，等其他复杂情况。
请在函数体内{}进行初始化操作。

3. **More Effective C++ 5**
- 谨慎定义类型转换函数。让编译器进行隐式类型转换所造成的弊端要大于它所带来的好处。一个参数进行调用的构造函数应当加上 explicit。比如单参数构造函数和多个参数且有默认值的构造函数。
- 在类型定义中, 类型转换运算符和单参数构造函数都应当用 explicit 进行标记. 一个例外是, 拷贝和移动构造函数不应当被标记为 explicit, 因为它们并不执行类型转换. 对于设计目的就是用于对其他类型进行透明包装的类来说, 隐式类型转换有时是必要且合适的. 这时应当联系项目组长并说明特殊情况.
不能以一个参数进行调用的构造函数不应当加上 explicit. 接受一个 std::initializer_list 作为参数的构造函数也应当省略 explicit, 以便支持拷贝初始化 (例如 MyType m = {1, 2};).（来自Google C++开源代码风格指南的3.2部分）

4. **Effective C++ 9**
不要在构造和析构函数中调用virtual函数,因为此过程调用的虚函数可能来自基类而不是派生类。

5. **More Effective C++ 10**
在构造函数中防止资源泄露
如果你用对应的智能指针对象替代指针成员变量，就可以防止构造函数在存在异常时发生资源泄露，你也不用手工在析构函数中释放资源，并且你还能像以前使用非CONST指针一样使用CONST指针，给其赋值。对于裸指针类型的成员，
如果像下面这样初始化则会出错，因为当new AudioClip抛出异常时，theImage会造成资源泄露。此时析构函数不会被调用，因为C++仅仅能删除被完全构造的对象，只有一个对象的构造函数完全运行完毕，这个对象才被完全地构造。
如果用try catch处理the Image的资源泄露当然可以就是不太优雅。使用智能指针则可以保证theImage的资源会被自动回收掉。
如果像下面这样初始化则会出错：
```cpp
class BookEntry { // 通讯录中的条目
public:
BookEntry(const string& name,
const string& address = "",
const string& imageFileName = "",
const string& audioClipFileName = ""): theName(name), theAddress(address),theImage(0), theAudioClip(0) {
	if (imageFileName != "") {
		theImage = new Image(imageFileName);
	}
	if (audioClipFileName != "") {
		theAudioClip = new AudioClip(audioClipFileName);
	}
}
~BookEntry();
...
private:
string theName; // 人的姓名
string theAddress; // 他们的地址
list<PhoneNumber> thePhones; // 他的电话号码
Image *theImage; // 他们的图像
AudioClip *theAudioClip; // 他们的一段声音片段
};
```


6. **派生类的默认构造函数的机制**
1、如果基类定义了不带参数的默认构造函数，则编译器为派生类自动生成的默认构造函数会调用基类的默认构造函数。
2、如果基类定义了拷贝构造函数，则编译器为派生类自动生成的拷贝构造函数同样会调用基类的拷贝构造函数。
3、如果基类定义了带参数的构造函数，派生类没有定义任何带参数的构造函数，则不能直接调用基类的带参构造函数，程序编译不通过。

7. **派生类的构造函数执行顺序**
按照继承顺序执行基类的构造函数，然后按定义顺序执行对象成员的构造函数。
1、调用基类构造函数。
顺序按照它们被继承时声明的顺序（从左向右）：Base2, Base1, Base3。
2、对初始化列表中的成员进行初始化。
顺序按照它们在类中定义的顺序：Base1 member1; Base2 member2; Base3 member3;。
对象成员初始化时自动调用其所属类的构造函数。由初始化列表提供参数。
3、执行派生类的构造函数体中的内容。

8. **More Effective C++ 4**
避免无用的缺省构造函数
缺省构造函数是常常被需要的，所以是可以提供的。也就是要保证缺省构造函数是合理的。
但是要避免提供无意义的缺省构造函数。提供无意义的缺省构造函数也会影响类的工作效率。如果成员函数必须测试所有的部分是否都被正确地初始化，那么这些函数的调用者就得为此付出更多的时间。而且还得付出更多的代码，因为这使得可执行文件或库变得更大。它们也得在测试失败的地方放置代码来处理错误。如果一个类的构造函数能够确保所有的部分被正确初始化，所有这些弊病都能够避免。缺省构造函数一般不会提供这种保证，所以在它们可能使类变得没有意义时，尽量去避免使用它们。使用这种（没有缺省构造函数的）类的确有一些限制，但是当你使用它时，它也给你提供了一种保证：你能相信这个类被正确地建立和高效地实现。
例如：
```cpp
class EquipmentPiece {
public:
	EquipmentPiece( int IDNumber = UNSPECIFIED);
	...
private:
	static const int UNSPECIFIED; // 其值代表 ID 值不确定。
};
```
这样的修改使得其他成员函数变得复杂，因为不再能确保 EquipmentPiece 对象进行了有意义的初始化。假设它建立一个因没有 ID 而没有意义的 EquipmentPiece 对象，那么大多数成员函数必须检测 ID 是否存在。如果不存在 ID，它们将必须指出怎么犯的错误。不过通常不明确应该怎么去做，很多代码的实现什么也没有提供：只是抛出一个异常或调用一个函数终止程序。当这种情形发生时，很难说提供缺省构造函数而放弃了一种保证机制的做法是否能提高软件的总体质量。

*总结*
1. 初始化成员列表的方式效率较高，使用初始化成员列表的时候，需要将成员变量都列出来，明确每个变量的构造方式。
2. 列表中成员变量的顺序最好和成员变量声明的顺序保持一致。复杂的初始化和成员之间相互初始化，则推荐在构造函数体中完成。
3. 单参数构造函数和多个参数且有默认值的构造函数,需要加上explicit，防止隐式转换。
4. 不要在构造和析构函数中调用virtual函数。

#### 析构函数
销毁对象时系统也会自动调用一个函数来进行清理工作，例如释放分配的内存、关闭打开的文件等，这个函数就是析构函数。
一般而言，有如下2种情况必须要写：
定义抽象接口时，必须要写虚析构函数，确保析构函数的多态性，防止资源泄露。
定义自定义RAII类时，使用析构函数去释放资源。
0. **类的成员变量如何被销毁**
如果类没有显示定义析构函数，那么编译器会为其提供一个缺省析构函数，缺省析构的函数体为空，在空析构函数执行完毕后，类中的成员会被自动销毁：
- 对基类类型成员变量，什么也不做
- 对类类型成员变量，将会自动调用相应类的析构函数
类中的成员的销毁过程依赖于成员类型，销毁类类型成员变量需要执行它自己的析构函数，而内置类型没有析构函数，因此销毁内置类型什么也不需要做。
1. **Effective C++ 7**
多态基类声明virtual析构函数。（Effective C++的第7节）
polymorphic多态性质的base classses应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥有一个virtual析构函数。
Classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不该声明virtual析构函数。
2. **Effective C++ 8**
别让异常从析构函数中抛出来，因为容器在析构的时候需要逐个调用元素的析构函数，如果多个元素都抛出异常，容器将无法正确处理，导致发生不可预测的错误。
在析构函数中如果遇到无法绕开的异常，可以尝试在析构函数内捕获异常并处理。
如果处理逻辑复杂，可以独立封装一个函数，用于在析构函数前执行。处理可能出现的异常，比如尝试重新关闭或者将异常记录下来。
3. **MORE Effective C++ 9**
资源应该被封装在一个对象里，遵循这个规则，你通常就能避免在存在异常环境里发生资源泄漏。
用一个对象存储需要被自动释放的资源，然后依靠对象的析构函数来释放资源，这种思想不只是可以运用在指针上，还能用在其它资源的分配和释放上。
4. **MORE Effective C++ 8**
讲解了这些操作符的区别：operator new; new operator;placement new;operator delete;delete operator;operator new[];operator delete[]。
operator new 分配内存。new operator 分配内存+构造对象。
operator delete 释放内存。delete operator 析构对象+释放内存。
operator new[];operator delete[]。分别是分配内存+调用元素的构造函数构造数组和调用元素的析构函数析构数组元素+释放内存

5. **string和内置类型需要在析构函数中操作释放内存吗？**
析构函数和构造函数类似，对于内置类型不做处理，对于裸指针类型会去调用delete，因此如果我们不写析构函数，但是对象存在动态开辟空间的行为，并且我们想释放这块开辟的空间，那么就会造成内存泄漏。
5.1 内置类型存储在栈中，所以函数退出栈就收回。内置类型没有析构函数,不存在调用析构的说法。
5.2 std::string中，字符串长度小于等于22时放在栈空间存储，否则字符串对象放在栈中，里面字符放到堆中存储。对象销毁的时候string成员变量的析构函数中会将堆中的内存回收。
https://zhuanlan.zhihu.com/p/510507837

6. **虚函数 vs 纯虚函数，如何选用？**
当基类中的某个成员方法，在大多数情形下都应该由子类提供个性化实现，但基类也可以提供缺省备选方案的时候，该方法应该设计为虚函数。
当基类中的某个成员方法，必须由子类提供个性化实现的时候，应该设计为纯虚函数。

7. **Effective C++ 9**
不要在构造和析构函数中调用派生类virtual函数。因为在构造和析构过程中，对象要么不是派生类对象，要么就是基类对象，这期间对象的状态不能使得调用者达到目的。

8. **new+delete**
C++中的 new 和 delete 分别用来分配和释放内存，它们与C语言中 malloc()、free() 最大的一个不同之处在于：用 new 分配内存时会调用构造函数，用 delete 释放内存时会调用析构函数。构造函数和析构函数对于类来说是不可或缺的，所以在C++中我们非常鼓励使用 new 和 delete。

9. **派生类的析构函数**
析构函数不被继承，派生类如果需要，要自行声明析构函数。
声明方法与无继承关系时类的析构函数相同。
不需要显式地调用基类的析构函数，系统会自动隐式调用。
具体执行顺序：
1，先执行派生类的析构函数
2，执行本类成员变量的析构函数
3，执行基类的析构函数

10. **虚析构函数**
类中如果出现virtual函数，那么这个类的析构函数也应该是virtual。
因为一般有virtual函数的地方，容易出现对多态的使用（声明基类指针变量，赋值给它派生类对象的指针）。这个要求是保证多态情况下，对象可以正确的销毁。

11. **Effective C++ 5**
class析构函数（无论是编译器生成的，还是用户自定义的），会自动调用其非静态成员变量的析构函数。

12. **More Effective C++ 11**
禁止异常信息exceptions传递到析构函数外
在有两种情况下会调用析构函数。第一种是在正常情况下删除一个对象，例如对象超出了作用域或被显示地delete。第二种是异常传递的堆栈辗转开解过程中，由异常处理系统删除一个对象。在上述两种情况下，调用析构函数时异常可能处于激活状态也可能没有处于激活状态。遗憾的是没有办法在析构函数内部区分出这两种情况。因此在写析构函数时你必须保守地假设有异常被激活。因为如果在一个异常被激活的同时，析构函数也抛出异常，并导致程序控制权转移到析构函数外，C++将调用terminate函数。这个函数的作用是终止你程序的运行，而且是立即终止，甚至连局部对象都没有被释放。
防止异常传递到析构函数外的主要办法就是使用 try catch语句，防止 try catch语句嵌套太深的办法是在最里面的catch块中，不写任何语句，保持空块。

*总结*
1. 多态用途的基类，需要声明virtual析构函数。
2. 别让异常从析构函数中抛出来，想办法在析构中处理，或将逻辑移到析构函数调用前处理。
3. 用一个对象存储需要被自动释放的资源，然后依靠对象的析构函数来释放资源，这种思想不只是可以运用在指针上，还能用在其它资源的分配和释放上。
4. 不要在构造和析构函数中调用virtual函数。

#### 继承
1. **Effective Modern C++ 12**
重写的函数需要添加override，这样可以减少错误发生。
如果不使用override，万一基类和派生类函数声明有错，则无法重写，且编译器又不会发生警告。
```cpp
class Base {
public:
virtual void mf1() const;
virtual void mf2(int x);
virtual void mf3() &;
virtual void mf4() const;
};
class Derived: public Base {
public:
virtual void mf1() const override;
virtual void mf2(int x) override;
virtual void mf3() & override;
void mf4() const override; // adding "virtual" is OK,
};
```
正确使用refernece qualifiers
```cpp
class Widget {
public:
using DataType = std::vector<double>;
…
DataType& data() & // for lvalue Widgets,
{ return values; } // return lvalue
DataType data() && // for rvalue Widgets,
{ return std::move(values); } // return rvalue
…
private:
DataType values;
};
Widget w;//
Widget makeWidget();//suppose we have a factory function that creates Widgets
auto vals1 = w.data(); // calls lvalue overload for Widget::data, copy-constructs vals1
//What’s needed is a way to specify that when data is invoked on an rvalue Widget, the
//result should also be an rvalue. Using reference qualifiers to overload data for lvalue
//and rvalue Widgets makes that possible:
auto vals2 = makeWidget().data(); // calls rvalue overload for Widget::data, move-constructs vals2
```
**父类私有虚函数子类是否可以override(重写)？**
答案是可以的。
 一个non-virtual 函数被定义为private时，它只能被该类的成员函数或友元函数所访问。而virtual修饰符则强调父类的成员函数可以在子类中被重写，因为重写之时并没有与父类发生任何的调用关系，故而重写是被允许的。
编译器不检查虚函数的各类属性。被virtual修饰的成员函数，不论它们是private、protect或是public的，都会被统一的放置到虚函数表中。对父类进行派生时，子类会继承到拥有相同偏移地址的虚函数表（相同偏移地址指，各虚函数相对于VPTR指针的偏移），则子类就会被允许对这些虚函数进行重载。且重载时可以给重载函数定义新的属性，例如public，其只标志着该重载函数在该子类中的访问属性为public，和父类的private属性没有任何关系！

2. **Effective C++ 32**
public继承意味着is-a关系，适用于base classes身上的每一件事情一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象。

3. **Effective C++ 33**
避免遮掩继承而来的名字。derived classes内的名称会遮掩base classes内的名称，在public继承下从来没有人希望如此。为了让被遮掩的名称再见天日，可适用using声明式或转交函数(forwarding functions)。
```cpp
//using声明式
class Base {
	private:
		int x;
	public:
		virtual void mf1() = 0;
		virtual void mf1(int);
		virtual void mf2();
		void mf3();
		void mf3(double);
}
class Derived: public Base{
	public:
		using Base::mf1; //让Base class内名为mf1和mf3的所有东西在Derived作用域内可见（并且public）
		using Base::mf3;
		virtual void mf1();
		void mf3();
		void mf4();
}
//转交函数
class Base{
	public:
		virtual void mf1() = 0;
		virtual void mf2(int)；
}；
class Derived: private Base{
	public:
		virtual void mf1(){Base::mf1();}//转交函数，暗自成为inline。
}
```

4. **Effective C++ 34**
接口继承和实现继承不同，在public继承之下，derived classes总是继承base class的接口。
pure virtual 函数只具体指定接口继承。
简谱的impure virtual函数具体指定接口继承及缺省实现继承。
non-virtual函数具体指定接口继承以及强制性实现继承。

5. **Effective C++ 35**
考虑virtual函数以外的其他选择
借由non-virtualinterface手法实现template method模式。
借由function pointers实现strategy模式，但是如果函数指针指向非成员函数那么无法访问成员变量。
借由tr1::function完成strategy模式，它可以解决函数指针方式无法访问成员变量的难题。现代C++已经有function了，所以用function。
古典的Strategy模式。

6. **Effective C++ 36**
绝不重新定义继承而来的non-virtual函数
D代表Derived类，B代表Base类，mf代表基类的函数。
如果Derived类重新定义mf，你的设计便出现矛盾。如果D真有必要实现出与B不同的mf,并且如果每一个B对象--不管多么特化--真的必须使用B所提供的mf实现码，那么“每个D都是一个B”就不为真。既然如此D就不该以public形式继承B。另一方面，如果D真的必须以public方式继承B，并且如果D真有需要实现出与B不同的mf，那么mf就无法为B反映出“不变性凌驾特异性”的性质。既然这样mf应该声明为virtual函数。最后，如果每个D真的是一个B，并且如果mf真的为B反映出“不变性凌驾特异性”的性质，那么D便不需要重新定义mf，而且它也不应该尝试这样做。

7. **Effective C++ 37**
绝对不用重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数--你唯一应该覆写的东西--却是动态绑定。
当你想另virtua函数表现出你所想要的行为但却遭遇麻烦，聪明的做法是考虑替代设计。其中NVI(non virtual interface)手法:令base class内的一个public non-virtual函数调用private virtual函数，后者可被derived classes重新定义，这里我们可以让non-virtual函数指定缺省参数，而private virtual函数负责真正的工作。

8. **Effective C++ 38**
通过复合塑膜出has-a或“根据某物实现出”
复合包括：分层，内含，聚合，内嵌。
在应用域中，复合意味着has-a。例如，程序中的对象其实相当于你所塑造的世界中的某些事务，例如人、汽车、一张张视频画面等。
在实现域，意味着is implemented in terms of（依赖某物实现），比如我们自己定义一个Set，Set内部依赖STL List这个类型的成员变量。

9. **Effective C++ 39**
- private继承意味is-implemented-in-terms of(根据某物实现出)。它通常比复合(composition)的级别低。但是当derived class需要访问protected base class的成员，或需要重新定义集成而来的virtual函数时，这么设计是合理的。
- 和复合不同，private继承可以造成empty base 最优化。这对致力于“对象尺寸最小化”的程序库开发者而言，可能很重要。

10. **Effective C++ 40**
谨慎使用多重继承。
- 多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual继承的需要。
- vitual继承会增加大小、速度、初始化复杂度等等成本。如果virtual base classes不带任何数据，将是最具实用价值的情况。
- 多重继承的确有正当用途。其中一个情节涉及“public继承某个interface class”和“private继承某个协助实现的class”的两相组合。
- 优先考虑单一继承，除非多重继承明显好于单一继承。

11. **More Effective C++ 3**
不要对数组使用多态。
假设声明了一个数组，元素为基类。但是实际装入数组中的元素是派生类。那么就很难通过下标准确取出元素。因为计算元素位置采用i*sizeof(基类)来得到具体位置。但是实际元素由于是派生类，那么取出的数据必然有问题。

12. **More Effective C++ 24**
理解虚拟函数、多重继承和虚基类、RTTI所需要的代价。都有可能增加类或对象占用的内存空间。
这个章节信息量比较大，需要阅读原文。但是这个章节不需要整理示例代码。

13. **More Effective C++ 33**
将非尾端类设计为抽象类。一般抽象类都是把析构函数定义为纯虚函数。

14. **不同继承方式下的访问权限差别**
```shell
基类中     继承方式      子类中
public ＆ public继承 => public
public ＆ protected继承 => protected
public ＆ private继承 = > private
protected ＆ public继承 => protected
protected ＆ protected继承 => protected
protected ＆ private继承 = > private
private ＆ public继承 => 子类无权访问
private ＆ protected继承 => 子类无权访问
private ＆ private继承 = > 子类无权访问
```
public继承意味继承接口和实现；protect继承意味继承部分接口和实现；private继承意味着只继承实现不继承接口。

15. **基类私有成员的可见性与存在性**
在类的继承中，基类私有成员在派生类中是“不可见“的，这种”不可见“是指在派生类的成员函数中，或者通过派生类的对象（指针，引用）不能直接访问它们。但是，不能直接访问并不代表不能访问。在派生类还是能够通过调用基类的共有函数的方式来间接地访问基类的私有成员，包括私有成员变量和私有成员函数。
但是不可见不意味着不存在，下面代码可以证明存在性。
```cpp
#include <iostream>
using namespace std;
class A {
	int i;
	void privateFunc() {
		cout<<"this is a private function of base class"<<endl;
	}

public:
	A(){i=5;}
};
class B:public A {
public:
	void printBaseI() {
		int* p=reinterpret_cast<int*>(this);//获取当前对象的首地址
		cout<<*p<<endl;
	}
	void usePrivateFunction() {
		void (*func)()=NULL;
		_asm
		{
			mov eax,A::privateFunc;
			mov func,eax;
		}
		func();
	}
};
int main() {
	B b;
	b.printBaseI();
	b.usePrivateFunction();
}
```
（1）虽然类 A 没有提供访问私有成员变量 i 的公有方法，但是在类 A（以及类 A 的派生类）对象中，都包含变量 i。
（2）虽然类 A 并没有提供访问私有成员函数 privateFunc() 的公有函数，但是在程序代码区依然存有函数 privateFunc() 的代码，通过内联汇编获取该函数的入口地址，仍然可以顺利调用。
这些是打印信息如下：
```
5
this is a private function of base class
```

16. **derived class可重新定义继承而来的private virtual函数**
Effective C++中有描述。

*总结*
内容太多不总结了。

#### 资源管理
1. **RAII**
参考：https://zhuanlan.zhihu.com/p/264855981
RAII 全称就Resource acquisition is initialization. 意为资源获取要通过构造函数初始化，然后析构函数负责释放资源。大部分时候又被用于做Scope Guard，Scope Guard同lambda服用，效果更佳，见下文。
```cpp
#include<functional>
#include<iostream>
class ScopeGuard
{
    std::function<void()> mFunc;
public:
    ScopeGuard(std::function<void()> f) {
        mFunc = f;
    }
    ~ScopeGuard() {
        mFunc();
    }
};
int doSomething(int* p) {
   return -1;
}
void f() {
   int* p = new int{3};
   ScopeGuard s([&p]() {
        if (p) {
            delete p;
        };
        std::cout << "delete point\n";
    });
   int error = doSomething(p);
   if (error) {
       return;
    }  
   std::cout<<"Function ends!\n";
   //ScopeGuard将执行自身析构函数，函数内部把p所指内存空间删除掉。
}
int main() {
    f();
}
```
**Effective C++ 13**
C++中常用的资源包括：文件描述器、互斥锁、图形界面中的文字和笔刷、数据库链接和网络sockets。无论哪一种资源，当你不再使用它时，必须将它还给系统。
为防止资源泄露，请使用RAII对象，他们在构造函数中获得资源并在析构函数中释放资源。
这里介绍的智能指针过时了，智能指针可以参考Effective ModernC++中的内容。

**Effective C++ 14**
在资源管理类中小心资源copying行为。
资源除了堆内存，还有锁，文件描述符，链接等。这些资源如果也想使用RAII的话，需要我们手动管理起来。
复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的拷贝行为。
普遍而常见的RAII class copying 行为是：抑制copying，施行引用计数法。不过其他行为也可能被实现，如：复制底部资源，转移底部资源的所有权。

**Effective C++ 15**
在资源管理类中提供对原始资源的访问。
RAII class并不是为了封装某物而存在；它们的存在是为了确保一个特殊行为--资源释放--会发生。
APIs 往往要求访问原始资源，所以每一个RAII class应该提供一个“取得其所管理之资源”的办法。
对原始资源的访问可能经由显示转换或隐式转换。一般而言显式转换比较安全，但隐式转换对客户比较方便。

**Effective C++ 16**
如果你在new表达式中使用了[]，必须在相应的delete表达式中使用[]。如果new表达式中没有使用[]，那么delete表达式中也不要使用[]。

**Effective C++ 17**
以独立语句将newed对象存储于(置入)智能指针内。如果这样做，一旦异常抛出，有可能导致难以察觉的资源泄露。

#### 智能指针
**裸指针为什么难用**
1. 裸指针的声明，无法表名它指向了一个对象还是数组。
2. 裸指针的声明，没有指出当你不使用的指针所指对象/数组的时候，是否应该销毁它。
3. 当你决定销毁指针所指对象/数组的时候，你不确定使用何种方式，使用delete还是其他专有函数。
4. 当你决定使用delete时，你不确定使用delete还是delete[]。
5. 当你确定销毁的方式以后，你需要确保每一个逻辑分支上都准确地销毁了指针所指资源。如果漏掉则会资源泄露，如果重复销毁，则会出现未定义定位。
6. 无法辨别一个指针是否是空悬指针(指针所指对象已经销毁)。
想使用好裸指针需要小心翼翼，很困难。

**智能指针的计数器**
计数器的实现依赖于，指针整型变量，每次赋值和复制，则对指针整型变量+1。因为源共享指针和目的共享指针都使用同一个内存区域存储技术，所以计数器+1后，两个共享指针中的计数器都会+1。

**Effective Modern C++ 18**
- std::unique_ptr 是一个具有开销小， 速度快， move-only 特定的智能指针， 使用独占拥有方式来管理资源。
- 默认情况下， 释放资源由delete来完成， 也可以指定自定义的析构函数来替代。 但是具有丰富状态的deleters和以函数指针作为deleters增大了 std::unique_ptr 的存储开销。
- 很容易将一个 std::unique_ptr 转化为 std::shared_pt。
- std::unique_ptr会产生两种格式，一种是独立的对象(std::unique_ptr),另外一种是数组(std::unique_ptr<T[]>)。因此，std::unique_ptr指向的内容从来不会产生任何歧义。

**Effective Modern C++ 19**
- 使用std::shared_ptr来管理共享式的资源，它是线程安全的。
- std::shared_ptr为了管理任意资源的共享内存管理提供了自动垃圾回收的便利。
- std::shared_ptr是std::unique_ptr的两倍大，除了控制块，还有需要原子引用计数操作引起的开销。
- 资源的默认析构一般通过delete来进行，但是自定义的deleter也是支持的。指向相同类型的智能指针，可以定义不同的deleter，当时这些智能指针类型是相同的，不受deleter影响。deleter的类型对于std::shared_ptr的类型不会产生影响。
- 避免从原生指针类型变量创建std::shared_ptr。
- 优先考虑使用unique_ptr，因为它性能更好，且可以被转换为std::shared_ptr。
- std::shared_ptr的API设计为指向单个的对象，不像std::unique_ptr的API即适合指向单个对象也适合指向数组。
- Curiously Recurring Template Pattern，CRTP，奇异递归模板模式。CRTP可以实现静态多态并精简代码，需要详细了解一下，https://zhuanlan.zhihu.com/p/54945314
*模板编程，使用CRTP实现一个例子*

**Effective Modern C++ 20**
- std::weak_ptr用来模仿类似std::shared_ptr的可悬挂指针
- 潜在的使用std::weak_ptr的场景包括缓存，观察者列表，以及组织std::shared_ptr形成的环

**Effective Modern C++ 21**
- 优先使用std::make_unique和std::make_shared而不是直接使用new
- 和直接使用new相比，使用make函数减少了代码的重复量，提升了异常安全度，并且，对于std::make_shared以及std::allocate_shared来说，产生的代码更加简洁快速。
- 也会存在使用make函数不适合的场景，对shared_ptr和unique_ptr来说：包含指定自定义的deleter，以及传递大括号initializer的需要。
- 对于std::shared_ptr来说，使用make函数的额外的不使用场景还包括(1)带有自定义内存管理的class:使用std::allocate_shared做内存分配；使用自定义的deleter做内存回收。(2)内存非常紧俏的系统，非常大的对象以及比对应的std::shared_ptr活的还要长的std::weak_ptr。

**Effective Modern C++ 22**
- 当使用Pimpl的时候在实现文件中定义特殊的成员函数
- Pimpl做法通过减少类的实现和类的使用之间的编译依赖减少了build次数。
- 对于std::unique_ptr pImpl指针，在class的头文件中声明这些特殊的成员函数，在class的实现文件中定义他们。即使默认的实现方式(编译器生成的方式)可以胜任也要这么做。
- 上述建议适用于std::unique_ptr，对std::shared_ptr无用。
- 链接实现一个Pimpl:https://zhuanlan.zhihu.com/p/458947637

*总结*
整理中
并在代码中整理代码出来。

#### 函数相关
1. 函数指针
```cpp
函数指针：是指向函数的指针变量，在C编译时，每一个函数都有一个入口地址，那么这个指向这个函数的函数指针便指向这个地址。
函数指针的用途是很大的，主要有两个作用：用作调用函数和做函数的参数。
函数指针的声明方法：
数据类型标志符 （指针变量名） （形参列表）；
一般函数的声明为: 
int func ( int x );
而一个函数指针的声明方法为：
int (*func) (int x);
前面的那个(*func)中括号是必要的，这会告诉编译器我们声明的是函数指针而不是声明一个具有返回型为指针的函数，后面的形参要视这个函数指针所指向的函数形参而定。
然而这样声明我们有时觉得非常繁琐，于是typedef可以派上用场了，我们也可以这样声明：
typedef int (*PF) (int x);
PF pf;
这样pf便是一个函数指针，方便了许多。当要使用函数指针来调用函数时，func(x)或者  (*fucn)(x) 就可以了，当然，函数指针也可以指向被重载的函数，编译器会为我们区分这些重载的函数从而使函数指针指向正确的函数。
```

2. 函数对象(仿函数)
```cpp
前面是函数指针的应用，从一般的函数回调意义上来说，函数对象和函数指针是相同的，但是函数对象却具有许多函数指针不具有的有点，函数对象使程序设计更加灵活，而且能够实现函数的内联（inline）调用，使整个程序实现性能加速。
函数对象：这里已经说明了这是一个对象，而且实际上只是这个对象具有的函数的某些功能，我们才称之为函数对象，意义很贴切，如果一个对象具有了某个函数的功能，我们变可以称之为函数对象。
如何使对象具有函数功能呢，很简单，只需要为这个对象的操作符()进行重载就可以了，如下：
class A{
public:
int operator()(int x){return x;}
};
A a;
a(5);
```
函数对象既然是一个“类对象”，那么我们当然可以在函数形参列表中调用它，**它完全可以取代函数指针！STL中便广泛的运用了这项技术。**如果说指针是C的标志，类是C++特有的，那么我们也可以说指针函数和函数对象之间的关系也是同前者一样的！（虽然有些严密）。当我们想在形参列表中调用某个函数时，可以先声明一个具有这种函数功能的函数对象，然后在形参中使用这个对象，他所作的功能和函数指针所作的功能是相同的，而且更加安全。

3. Lambda表达式
lambda：需要C++ 11之后支持，可以认为是用编译器帮你实现了仿函数对象，可以简化很多不必要的命名。

4. c++函数进化史 （函数，函数指针，function，仿函数，lambda）
https://zhuanlan.zhihu.com/p/561916691
lambda的底层实现是仿函数，一般lambda使用起来比仿函数要方便一些。
lambda表达式在很多地方也可以替代函数指针，一般lambda也比函数指针方便。
function在很多地方都可以替代函数指针，
function与函数指针很像。std::function是一个可变参类模板，是一个通用的函数包装器（Polymorphic function wrapper）。std::function的实例可以存储、复制和调用任何可复制构造的，包括普通函数、、类对象（重载了operator()的类的对象）、Lambda表达式等。是对C++现有的可调用实体的一种类型安全的包裹（相比而言，函数指针这种可调用实体，是类型不安全的）。
```cpp
#include <functional>
#include <iostream>
 
struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
 
int main()
{
    // 存储自由函数
    std::function<void(int)> f_display = print_num;
    f_display(-9);
 
    // 存储 lambda
    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();
 
    // 存储到 std::bind 调用的结果
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();
 
    // 存储到成员函数的调用
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);
    f_add_display(314159, 1);
 
    // 存储到数据成员访问器的调用
    std::function<int(Foo const&)> f_num = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';
 
    // 存储到成员函数及对象的调用
    using std::placeholders::_1;
    std::function<void(int)> f_add_display2 = std::bind( &Foo::print_add, foo, _1 );
    f_add_display2(2);
 
    // 存储到成员函数和对象指针的调用
    std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
    f_add_display3(3);
 
    // 存储到函数对象的调用
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
 
    auto factorial = [](int n) {
        // 存储 lambda 对象以模拟“递归 lambda ”，注意额外开销
        std::function<int(int)> fac = [&](int n){ return (n < 2) ? 1 : n*fac(n-1); };
        // note that "auto fac = [&](int n){...};" does not work in recursive calls
        return fac(n);
    };
    for (int i{5}; i != 8; ++i) { std::cout << i << "! = " << factorial(i) << ";  "; }
}
```

#### 并发编程

**Effective Modern C++ 16**
让const成员函数线程安全
一定要确保const成员函数线程安全，除非你确定它们永远不会在并发上下文（concurrent context）中使用。
使用std::atomic变量可能比互斥量提供更好的性能，但是它只适合操作单个变量或内存位置。

**Effective Modern C++ 35**
优先考虑基于任务的编程而非基于线程的编程
- std::thread API不能直接访问异步执行的结果，如果执行函数有异常抛出，代码会终止执行。
- 基于线程(std::thread)的编程方式需要手动的线程耗尽、资源超额、负责均衡、平台适配性管理。
- 通过带有默认启动策略的std::async进行基于任务的编程方式会解决大部分问题。

**Effective Modern C++ 36**
如果有异步的必要请指定std::launch::async
- std::async的默认启动策略是异步和同步执行兼有的。
- 这个灵活性导致访问thread_locals的不确定性，隐含了任务可能不会被执行的意思，会影响调用基于超时的wait的程序逻辑。
- 如果异步执行任务非常关键，则指定std::launch::async。

**Effective Modern C++ 37**
- 在所有路径上保证thread最终是不可结合的。
- 析构时join会导致难以调试的表现异常问题。
- 析构时detach会导致难以调试的未定义行为。
-  声明类数据成员时，最后声明std::thread对象。
*HERE 考虑为本节写个RAII管理thread结合性的例子*

**Effective Modern C++ 38**

**Effective Modern C++ 39**

**Effective Modern C++ 40**

*HERE，搞完这些就直接从Effective Modern C++ 23继续*



*在网上找找Effecti C++和More Effective C++的哪些条款已经不适用现代C++语法了。更新一下笔记*
*在面向对象部分的信息整理完成后，再跟CGL对应章节核对一遍*

### 模板元编程(编译期计算)语法

#### 资料
C++模板元编程详细教程(已经保存到WIZNOTE中)
https://blog.csdn.net/fl2011sx/article/details/128077440

C++ 11 14 17的模板元编程语法(已经保存到WIZNOTE中)
https://zhuanlan.zhihu.com/p/672410503

#### 计划
学习C++模板元编程详细教程：https://blog.csdn.net/fl2011sx/article/details/128077440
然后整理出一个代码示例在ModerCppStarter中，然后再阅读Effective Modern C++，和EffectiveC++部分，将这些内容整理在此NOTE.md笔记中。

**什么是模板元编程**
从这个模板元的元老中可以看出，它有2个要素，一个是用于静态判断的cond，另一个是用于类型处理的T。所以，模板元编程无非就是做两件事，一个是静态数学计算（包括了布尔类型的逻辑运算和整数类型的数值运算。这里的「静态」是指编译期行为。）；另一个是类型处理（type traits，也被翻译为「类型萃取」）。
所以，静态计算和类型处理的编写过程，就称为「模板元编程」。把这两个要素的结果放到enable_if（或类型行为的模板）中，再通过SFINAE特性生成需要的代码再去参与编译。
强调一下，模板元编程是完完全全的编译期行为，任何设计运行期才能确定的数据都不可用，因此我们的编程思维跟普通代码编写的思维也是完全不同的，请读者一定要注意。
**两个要素**
静态计算和类型处理

##### 模板元编程相关语法
**Effective Modern C++ 1**
```cpp
template<typename T> void f(ParamType param);
f(expr);
```
在编译的时候， 编译器通过 expr 来进行推导出两个类型： 一个是 T 的， 另一个是 ParamType 。 通常来说这些类型是不同的， 因为 ParamType 通常包含一些类型的装饰， 比如 const 或引用特性。 
`template<typename T> void f(T& param);`
在模板类型推导的时候， 有引用特性的参数的引用特性会被忽略。也就是T的类型不带引用。T的类型可以带const也可以不带const。
在推导通用引用参数的时候， 左值会被特殊处理。 T 和 ParamType 都会被推导成左值引用。
在推导按值传递的参数时候， const 和/或 volatile 参数会被视为非 const 和非 volatile。
在模板类型推导的时候， 参数如果是数组或者函数名称， 他们会被退化成指针， 除非是用在初始化引用类型。

**Effective Modern C++ 2**
理解auto类型推导。
auto类型推导通常和模板类型推导一样。除了一点：auto类型推导假定花括号初始化代表的类型是std::initializer_list,但是模板类型推导却不是这样。
auto在函数返回值或者lambda参数里面执行模板的类型推导，而不是通常意义的auto类型推导。

**Effective Modern C++ 3**
理解decltype
decltype几乎总是得到一个变量或表达式的类型而不需要任何修改。
对于非变量名的类型为 T 的左值表达式， decltype 总是返回 T&。
C++14 支持 decltype(auto) ， 它的行为就像 auto ,从初始化操作来推导类型， 但是它推导类型时使用 decltype 的规则。
```cpp
template<typename Container, typename Index> // C++14;
auto authAndAccess1(Container &c, Index i) // not quite
{ // correct
	authenticateUser();
	return c[i];
}

void test1(){
	std::deque<int> d;
	...
	authAndAccess1(d, 5) = 10; // authenticate user, return d[5], then assign 10 to it; this won't compile!
}

template<typename Container, typename Index> // C++14; works,
decltype(auto) // but still
authAndAccess2(Container &c, Index i) // requires
{ // refinement
	authenticateUser();
	return c[i];
}

void test2(){
	std::deque<int> d;
	...
	authAndAccess2(d, 5) = 10; // success compile!
}
```
**Effective Modern C++ 4**
指导如何查看类型推导。优先使用Boost TypeIndex库因为它最准确。
类型推导的结果常常可以通过IDE的编辑器， 编译器错误输出信息和Boost TypeIndex库的结果中得到。
一些工具的结果不一定有帮助性也不一定准确， 所以对C++标准的类型推导法则加以理解是很有必要的。
```cpp
#include <boost/type_index.hpp>
template<typename T>
void f(const T& param)
{
	using std::cout;
	using boost::typeindex::type_id_with_cvr;
	// show T
	cout << "T = "
	<< type_id_with_cvr<T>().pretty_name()
	<< '\n';
	// show param's type
	cout << "param = "
	<< type_id_with_cvr<decltype(param)>().pretty_name()
	<< '\n';
	…
}
```

##### 一 模板分类
要问C++模板有哪些分类:
1. 模板类
2. 模板函数
3. 模板全局常量
4. 模板类型重命名

- 类模板
class,union和struct都可以模板化。
```cpp
template <typename T, size_t size>
class Array {
 public:
  Array();
  T &at();
  size_t size() const;
 private:
  T data_[size];
};

void Demo() {
  Array<int, 5> arr; // 实例化，并创建对象
  arr.at(1) = 6;
}
```
- 模板函数,模板函数就是用模板生成一个函数，主体是一个函数。当然，普通函数、成员函数、包括lambda表达式都是可以写成模板的。
```cpp
// 普通模板函数
template <typename T>
void show(const T &item) {
  std::cout << item << std::endl;
}

class Test {
 public:
  // 模板成员函数
  template <typename T>
  void mem_func(const T &item) {}
};

// 模板lambda表达式（只能是全局变量承载）
template <typename T>
auto f = [](const T &item) {}

void Demo() {
  show<int>(5);
  
  Test t;
  t.mem_func<double>(5.1);
  
  f<char>('A');
}
```
- 模板全局常量
模板的全局常量一般是由一个模板类来做「引导」的，而且由于模板必须在编译期实例化，因此模板全局常量一定也会在编译期有一个确定的值，必须由constexpr修饰，而不可以是「变量」.
```cpp
// 用于引导模板全局常量的模板类(用于判断一个类型的长度是否大于指针)
template <typename T>
struct IsMoreThanPtr {
  static bool value = sizeof(T) > sizeof(void *);
};
// 全局模板常量
template <typename T>
constexpr inline bool IsMoreThanPtr_v = IsMoreThanPtr<T>::value;
```
- 模板类型重命名
C++中的类型重命名主要有两种语法，一种是typedef，另一种是using，它们都支持模板生成，效果是相同的。
模板类型重命名可以直接借用一个模板类来做「偏特化」，或者也可以像模板全局常量一样由一个模板类来引导，请看下面例程：
```cpp
// 普通的模板类
template <typename T, size_t size>
class Array {};
// 偏特化作用的模板类型重命名
template <typename T>
using DefaultArray = Array<T, 16>;
// 也可以作用给typedef语法
template <typename T>
typedef DefaultArray<T *> DefaultPtrArray;

void Demo() {
  DefaultArray<int> arr1; // 相当于Array<int, 16> arr1;
  DefaultPtrArray<char> arr2; // 相当于Array<char *, 16> arr2;
}
// 用于引导的模板类
template <typename T> struct GetPtr {
  using type = T *;
};
// 用模板类引导的模板类型重命名
template <typename T> 
using GetPtr_t = typename GetPtr<T>::type;

void Demo() {
  GetPtr_t<int> p; // 相当于typename GetPtr<int>::type p; 也相当于int *p;
}
```

C++的模板参数分类：
1. 类型
2. 整数
3. 模板

- 类型模板参数
show是一个模板函数，接受1个参数T，并且它是一个类型参数。实例化的时候，就需要在T的位置传入一个类型标识符（例如int、void *或者std::string）。
类型模板参数除了直接使用以外，还可以和其他符号（比如*、&、&&、const等）进行组合。<typename T>typename关键字表示类型参数，也可以写<class T>，推荐使用typename。
```cpp

template <typename T>
void show(T t) {
  std::cout << t << std::endl;
}
void Demo() {
  show<int>(5);
  show<void *>(nullptr);
  show<std::string>("abc");
}
```
- 整数模板参数
那么这里的size就是整数，当然不止size_t类型，一切整型都是支持的，比如说int、short、char，甚至bool都是可以。模板是编译期语法，因此，这里的整型数据也必须是编译期能确定的，比如说常数、常量表达式等，而不可以是动态的数据。
```cpp
template <typename T, size_t size>
class Array {
  // ...
 private:
  T data[size];
};
// 整数参数的模板
template <int N>
struct Test {};

void Demo() {
  Test<5> t1; // 常数OK

  constexpr int a = 5;
  Test<a> t2; // 常量表达式OK

  const int b = 6;
  Test<b> t3; // ERR，b是只读变量，不是常量

  Test<a * 3> t4; // 常数运算OK

  std::vector<int> ve {1, 2, 3};
  Test<ve.size()> t5; // ERR，size是运行时数据
  Test<ve[1]> t6; // ERR，ve的成员是运行时数据

  int arr1[] {1, 2, 3};
  Test<arr1[0]> t6; // ERR，arr1的成员是运行时数据

  constexpr int arr2[] {2, 4, 6};
  Test<arr2[1]> t7; // 常量表达式修饰的普通数组成员OK
}
```
- 浮点数
在C++20以前，只允许整数参数，但从C++20起，可以支持浮点数做参数，同样，只要是编译期能确定的量就OK：
- 整数的衍生类型
说到整数的衍生类型，也就是说「可以用整数表示」，或者说「本质上是整数」的类型。
- 指针类型
如果说某一个变量，它的地址在程序运行期间能够一直不发生改变，或者说它不会中途被释放的话，我们就认为这个变量的地址是「确定的」。只要是「程序运行中确定的」地址，就可以用来实例化模板。
```cpp
template <int *p>
void f(int data;) {
  *p = data;
}
int a = 1; // 全局变量

class Test {
 public:
  int m1; // 成员变量
  static int m2; // 静态成员变量
};

int Test::m2 = 4;

void Demo() {
  int b = 2; // 局部变量
  static int c = 3; // 静态局部变量
  
  f<&a>(0); // OK，a是全局变量，程序运行期间不会被释放
  f<&b>(0); // ERR，b是局部变量，在局部代码块运行完毕后会被释放，所以说b的地址也有可能不仅仅表示b，回收后可能会表示其他数据，所以不可以
  f<&c>(0); // OK，c是静态局部变量，不会随着代码块的结束而释放
  
  f<&Test::m1>(0); // ERR，Test::m1其实并不是变量，要指定了对象才能确定，因此是非确定值，所以不可以
  f<&Test::m2>(0); // OK，Test::m1本质就是一个全局变量，在程序运行期间不会被释放，所以OK
}
```
- 函数类型
函数指针类型
既然讲到指针类型，那我们也逃不开一类特殊的指针——函数指针。函数指针其实本质上也是地址，所以同样属于整数的衍生类型。而分配给函数（指令段）的地址在程序执行过程中就是不会变的，但如果用的是变量的值那么同样会因为动态数据问题而报错。
```cpp
// 函数指针类型模板参数
template <void (*func)()>
void f() {
  func();
}

// 普通函数
void f1() {}

class Test {
 public:
  void f2() {} // 成员函数
  static void f3() {} // 静态成员函数
};

void Demo() {
  void (*pf1)() = &f1; // 局部变量
  constexpr void (*pf2)() = &f1; // 常量表达式

  f<&f1>(); // OK，函数本身就是地址不可变的
  f<&Test::f2>(); // ERR，虽然成员函数也是地址不可变的，但&Test::f2的类型是void (Test::*)()，类型不匹配所以报错
  f<&Test::f3>(); // OK，静态成员函数是地址不可变的，类型也匹配
  f<pf1>(); // ERR，pf1是静态数据，编译期值不确定，所以不可以
  f<pf2>(); // OK，用常量表达式修饰的在编译期可以确定，所以可以
}
```
函数类型
```cpp
// 函数类型模板参数
template <void func()>
void f() {
  func();
}

// 普通函数
void f1() {}

class Test {
 public:
  void f2() {} // 成员函数
  static void f3() {} // 静态成员函数
};

void Demo() {
  void (*pf1)() = &f1; // 局部变量
  constexpr void (*pf2)() = &f1; // 常量表达式

  f<f1>(); // OK
  f<&f1>(); // OK
  f<Test::f3>(); // OK
  f<&Test::f3>(); // OK
  f<pf2>(); // OK
  // 与前一例程相同，不再赘述
}
```
模板类型
这个类型非常容易让人晕菜，所谓「模板类型的模板参数」，其实就是嵌套模板的意思，把「某一种类型的模板」作为一个参数传给另一个模板。请看示例：
```cpp
// 模板类型的模板参数
template <template <typename, typename> typename Tem>
void f() {
  Tem<int, std::string> te;
  te.show();
}

// 符合条件的模板类
template <typename T1, typename T2>
struct Test1 {
  void show() {std::cout << 1 << std::endl;}
};

template <typename T1, typename T2>
struct Test2 {
  void show() {std::cout << 2 << std::endl;}
};

// 不符合条件的模板类
template <int N>
struct Test3 {
  void show() {std::cout << 3 << std::endl;}
};

void Demo() {
  f<Test1>(); // 注意这里，要传模板，而不是实例化后的模板
  f<Test<int, int>>(); // ERR，模板参数类型不匹配
  
  f<Test2>(); // OK
  f<Test3>(); // ERR，类型不匹配
}
```
- 变参模板
所谓的「变参」指的是「参数数量可以是任意的」，变参模板并不是独立的一种类型参数，我们可以认为它是「一组参数」，可以是一组类型参数，也可以是一组非类型参数。
```cpp
template <typename... Args> auto sum(Args... args) {
  return (... + args);
}
// 以下是测试Demo
void Demo() {
  auto a = sum(1, 2, 3, 4); // 10
  auto b = sum(1.5, 2, 3l); // 6.5
  auto c = sum(std::string("abc"), "def", "111"); // std::string("abcdef111")
  auto d = sum(2); // 2
}
```
相信读者不难看得出，这三个点就表示变参，不过三个点书写的位置是有讲究的，不同的位置表示的含义也略有不同。在上面的例子中，模板参数含有一个typename... Args，其中的三个点顿在了typename后面，表示这是一组类型参数，可以叫它「包（pack）」，而后面的Args就是这个「包」的名字。那么我们就知道，Args代表的并不是一个单一类型，而是一组类型参数组成的包。注意，模板的变参结构跟其他变参结构类似，都是只能出现一次，并且必须在列表最后，否则会造成解析的歧义。同时，变参结构在实际传递时，参数可以为空。
在函数参数中，可以看到有个Args...，由于Args本身是个包，那么给包后面加三个点表示「解包（Unpack）」，或者叫「展开（Unfold）」。所以参数中的解包，我们可以解读为，把Args中的每一个类型，平铺开，每一个类型都要对应一个函数的入参。而后面的args代表的就是这一组参数，它同样是一个「包」，但它则是由形参（本质就是局部变量）组成的包。
函数体中，可以看到出现了(... + args)的表达式，大家应该能猜到，这也是一种「解包」的语法，但这属于「按符号解包」的方式，与之对应的还有一种「直接解包」的方式，下面来分别讲解。

- 变参的直接展开
所谓「直接展开」，其实指的是按「逗号」展开，逗号不仅仅指逗号运算，任何以逗号为分割符的地方都支持变参的展开。比如说，给一片自定义的内存资源池适配一个创建对象的方法，就可以这样来写（简化一下，先不考虑左右值传递的问题）：
```cpp
std::byte memory[16384]; // 这是一片内存资源池
void *head = memory; // 可用空间的头指针
// 在内存资源池上创建对象的函数
template <typename T, typename... Args>
T &Create(Args... args) {
  auto &obj = *new(head) T(args...);
  head += sizeof(T);
  return obj;
}
struct Test {
  Test(int, double) {}
};

void Demo() {
  auto test = Create<Test, int, double>(1, 2.5); // 会通过Test(int, double)构造函数构造
}
```
上面实例化的Create<Test, int, double>类型，首先模板参数在展开的时候，Args中含有两个类型，分别是int, double，这里就是用逗号展开的。后面的args中也是含有两个变量，同样是按照逗号隔开，所以其实实例化后的函数是这样的：
```cpp
Test &Create(int arg1, double arg2) {
  auto &obj = *new(head) Test(arg1, arg2);
  head += sizeof(Test);
  return obj;
}
```
- 变参的嵌套展开
刚才我们介绍的是直接展开，但有时可能我们要在变参的基础上嵌套一个什么结构，然后再展开的。
```cpp
// 把数组中的某些角标元素取出来，组成新数组
template <typename T, int... N>
std::vector<T> GetSubVector(const std::vector<T> &src) {
  return std::vector<T> {src.at(N)...};
}

// 示例Demo
void Demo() {
  std::vector<int> ve {0, 11, 22, 33, 4};
  auto ve2 = GetSubVector<int, 1, 4, 1, 3, 0>(ve);
  // 执行后ve2会变成{11, 4, 11, 33, 0}
}
```
上面这个例子中，N是一个包，并且是整数包，对它展开的时候就没有用N...这样直接展开，而是加了一层结构，按照src.at(N)...的方式展开。这样展开后，每一个参数都会嵌套相同的结构，并且它们之间也是用逗号隔开的。所以GetSubVector<int, 1, 4, 1, 3, 0>其实会实例化成：
```cpp
std::vector<int> GetSubVector(const std::vector<int> &src) {
  return std::vector<int> {src.at(1), src.at(4), src.at(1), src.at(3), src.at(0)}; // N的嵌套方式展开
}
```
- 按照符号展开
在C++17以前，变参只可以用逗号展开。
```cpp
// 递归终止条件（只有1个参数的情况）
template <typename T>
auto sum(T arg) {
  return arg;
}

// 2个以及以上的情况要进行递归
template <typename Head, typename... Args>
auto sum(Head head, Args... args) {
  return head + sum<Args...>(args...);
}
```

```cpp
void Demo() {
  auto a = sum<double, int, int, double>(1.5, 2, 2, 1.6);
}
//首先，sum<double, int, int, double>不符合只有1个参数的条件，所以会命中下面的模板，实例化后的样子是：
auto sum(double head, int arg0, int arg1, double arg2) {
  return head + sum<int, int, double>(arg0, arg1, arg2);
}
//它会要求调用一个sum<int, int, double>函数，所以会继续实例化：
auto sum(int head, int arg0, double arg1) {
  return head + sum<int, double>(arg0, arg1);
}
//又会要求调用一个sum<int, double>，继续实例化：
auto sum(int head, double arg0) {
  return head + sum<double>(arg0);
}
//又会要求调用一个sum<double>，但是此时，命中了上面的模板定义，所以会按照上面的方式来实例化，变成：
auto sum(double arg) {
  return arg;
}
```
C++17提供了另一种变参展开方式，就是按照一个特定的符号展开（而不是逗号），可以极大程度上简化问题，
这里的(... + args)就是折叠表达式，表示按照加号展开。我们知道，运算符是有优先级和合并顺序的，因此要按符号展开，就必须指定这种展开顺序，换句话说，((a ⊕ b) ⊕ c)和(a ⊕ (b ⊕ c))到底选哪一种的问题（这里的「 ⊕ 」代指任意二元运算符）。
对于这个问题，C++的解决方案是通过变参包名和三个点的位置来示意（注意，这里就是一种强行的规定，没什么道理可言），三个点在左的，表示从左到右合并；三个点在右边的，表示从又到左合并。
我们刚才提到，折叠表达式只支持二元运算符，既然是二元运算符，如果遇到只有一个参数的时候怎么办呢？这时这个符号会被忽略，直接返回原值。
```cpp
template <typename... Args>
auto sum(Args... args) {
  return (... + args);
}
```
假如说我并不是希望仅仅包内的内容自行结合，而是要结合一个额外的内容呢？
要「把第一个参数先跟cout结合，第二个参数应当跟前面的运算结果（同样还是cout）再集合，之后都是依次跟前面的结合」。
```cpp
template <typename... Args>
void Show(Args... args) {
  (std::cout << ... << args); // 注意括号还是不能丢
}
//展开后的形式为：
//((((std::cout << arg0) << arg1) << ...) << argn)
```
我们把这种有额外内容参与的展开方式称为「二元展开」，相对的，前面那种方式就叫「一元展开」。注意，这里的「一元」「二元」并不表示运算符，因为不管是一元展开还是二元展开，都只能用二元运算符展开。这里的几元表示的是参与展开的成员有几个，如果只有一个包，自己内部展开的，就叫「一元展开」；而这种除了一个包，还需要一个额外内容参与展开的，就叫「二元展开」了。同理，二元展开也有向右展开的版本：`(args ⊕ ... ⊕ obj)`
```cpp
(a + ... + args); // 二元展开，从左侧开始，先与a结合
(args ^ ... ^ a); // 二元展开，从右侧开始，先与a结合
(a - args - ...); // ERROR！语法错误
(... & args & a); // ERROR！语法错误
a - (args - ...); // 一元展开，展开后再与外面的内容进行运算
(... & args) & a; // 一元展开，展开后再与外面的内容进行运算
```

##### 二 模板参数自动推导
模板参数自动推导：
1. 根据函数参数自动推导（模板函数）
2. 根据构造参数自动推导（模板类）
3. 自定义构造推导（模板类）

- 根据函数参数自动推导
模板参数的自动推导是完全按照auto的推导原则进行的,仅仅保留「最简类型」。
```cpp
template <typename T>
void show(T t) {
  std::cout << t << std::endl;
}

void Demo() {
  int a = 5;
  show(a); // [1],触发模板参数的自动推导。此时相当于show<int>(a)
  show(5); // [2],触发模板参数的自动推导。此时相当于show<int>(5)
}

template <typename T>
void f1(T &t) {}

template <typename T>
void f2(const T &t) {}

template <typename T>
void f3(T *p) {}

void Demo() {
  f1(5); // 会报错，因为会推导出f1<int>，从而t的类型是int &，不能绑定常量
  int a = 1;
  f1(a); // f1<int>，t的类型是int &
  f2(a); // f2<int>，t的类型是const int &
  f3(a); // 会报错，因为会推导出f3<int>，此时t的类型是int *，int不能隐式转换为int *
  f3(&a); // f3<int>， t的类型是int *
}
```
T &&也可以绑定可变值
1. 当T &&匹配到可变值（也就是C++11里定义的「左值」）的时候，T会推导出左值引用，再根据引用折叠原则，最终实例化为左值引用
2. 当T &&匹配到不可变值（也就是C++11里定义的「右值」）的时候，T会推导出基本类型，最终实例化为右值引用
对于auto &&来说，我们只关心最终推导出的类型，并不会关心auto本身到底代表了什么。但对于模板的类型推导则不同，我们既要关心「模板参数推导出了什么类型」，又要关心「模板实例化后的函数参数是什么类型」。换做上面的例子来说就是，我们既要关系T推导出了什么，又要关心当T确定以后，t会变成什么类型。
```cpp
template <typename T> void f4(T &&t) {}
void Demo() {
  int a = 5;
  const int b = 10;
  f4(1); // f4<int>，t的类型是int &&。利用函数参数自动推导出的模板参数永远不会推导出右值引用，T不为右值引用。
  f4(a); // f4<int &>，t的类型是int &
  f4(b); // f4<const int &>，t的类型是const int &
  f4(std::move(a)); // f4<int>，t的类型是int &&
}
```
除了与引用、指针等组合外，还可以跟其他模板进行嵌套组合，编译器同样可以推导出正确的类型，请看例程：
```cpp
template <typename T>
struct Test {};

template <typename T>
void f(const Test<T> &t) {}

void Demo() {
  Test<int> t1;
  Test<char> t2;

  f(t1); // 推导出f<int>，t的类型是const Test<int> &
  f(t2); // 推导出f<char>，t的类型是const Test<char> &
}
```
这种技巧非常适用于各种模板库（比如说STL），例如我们希望把一个vector的内容连续地放入一个buffer中，就可以这样来写：
```cpp
#include <vector>
#include <cstdlib>
#include <cstddef>

template <typename T>
void CopyVec2Buf(const std::vector<T> &ve, void *buf, size_t buf_size) {
  if (buf_size < ve.size() * sizeof(T)) {
    return;
  }
  std::memcpy(buf, ve.data(), ve.size() * sizeof(T));
}

void Demo() {
  std::vector<int> ve{1, 2, 3, 4};
  std::byte buf[64];
  // 把ve的内容连续地复制到buf中
  CopyVec2Buf(ve, buf, 64); // 这里会推导出CopyVec2Buf<int>
}
```

- 模板类是通过构造参数来推导
```cpp
template <typename T1, typename T2>
class Pair {
 public:
  Pair(const T1 &t1, const T2 &t2);
  void show() const;
 private:
  T1 t1_;
  T2 t2_;
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const T1 &t1, const T2 &t2) : t1_(t1), t2_(t2) {}

template <typename T1, typename T2>
void Pair<T1, T2>::show() const {
  std::cout << "(" << t1_ << ", " << t2_ << ")" << std::endl;
}

void Demo() {
  Pair pair1{'a', 3.5}; // Pair<char, double>
  pair1.show();
  
  int a = 5;
  std::string str = "abc";
  
  Pair pair2{a, str}; // Pair<int, std::string>
  pair2.show();
}
```
自定义构造推导
为了「促使」模板类能够按照我们希望的方式来进行类型推导并实例化，当我们发现自动的类型推导不满足需求的时候，就可以考虑添加一种自定义的构造推导，这个语法称之为「推导指南(Deduction Guide)」。当定义了推导指南后，编译期会优先根据推导指南来进行实例化，如果没有合适的推导指南，才会根据构造函数参数来进行实例化。
相信有的读者看到这里会想，这不是废话嘛……本来不也是按这种方式推导的呀？但其实并不是！因为推导指南会按照函数调用法则来识别，也就是说，这里的Test(T)应当看做一个函数，当我们把const char [4]类型的参数传进函数参数的时候，就会转换为const char *。所以拥有了推导指南后，T会识别为const char *，再根据指南，实例化的结果就是Test<const char *>了。
```cpp
template <typename T>
struct Test {
  Test(const T &t): mem_(t) {}
  T mem_;
};

// Deduction Guide
template <typename T>
Test(T)->Test<T>;

void Demo() {
  Test t{"abc"}; // Test<const char *>
}
```
##### 三 模板特化
这里的问题就在于，对于字符串类型（这里指原始C字符串，而不是std::string）来说，「相加」并不是简单的+=，因为字符串主要是用字符指针来承载的，指针相加是不合预期的。我们希望的是字符串拼接。
因此，我们希望，单独针对于char *的实例化能够拥有不同的行为，而不遵从「通用模板」中的定义。这种语法支持就叫做「特化」，或「特例」。可以理解为，针对于模板参数是某种特殊情况下进行的特殊实现。
因此，我们在通用模板的定义基础上，再针对char *类型定义一个特化：
```cpp
#include <cstring>

template <typename T>
void add(T &t1, const T &t2) {
  t1 += t2;
}

template <> // 模板特化也要用模板前缀，但由于已经特化了，所以参数为空
void add<char *>(char *&t1, char *const &t2) { // 特化要指定模板参数，模板体中也要使用具体的类型
  std::strcat(t1, t2);
}

void Demo() {
  int a = 1, b = 3;
  add(a, b); // add<int>是通过通用模板生成的，因此本质是a += b，符合预期

  char c1[16] = "abc";
  char c2[] = "123";

  add(c1, c2); // add<char *>有定义特化，所以直接调用特化函数，因此本质是strcat(c1, c2)，符合预期
}
```
- 编译与链接问题
模板实现需要放在头文件里，才能正确的编译和链接。
否则编译可以通过，但是链接会出问题。详细可参考原文：https://blog.csdn.net/fl2011sx/article/details/128314495

- 全特化
全特化的模板其实已经不是模板了，在这里f<int>会按照普通函数一样来进行编译和链接。所以直接把实现放在头文件中，就有可能在链接时重定义。解决方法有两种，第一种就是我们手动补上inline关键字，提示编译期要打标全局唯一。
```cpp
#pragma once
template <typename T>
void f(T t) {} // 通用模板，编译器用通用模板生成的实例会自动打上inline

template <>
inline void f<int>(int t) {} // 针对int的全特化，必须手动用inline修饰后才能在编译期打标保证链接全局唯一
```
第二种方法就是，当做普通函数处理，我们把实现单独抽到一个编译单元中独立编译，最后在链接时才能保证唯一：
```cpp
//tmp.h
#pragma once
template <typename T>
void f(T t) {} // 通用模板

template <>
void f<int>(int t); // 针对int的全特化声明（函数声明）

//tmp.cpp
#include "tmp.h"

template <>
void f<int>(int t) {} // 函数实现
```
另外，对于特化的模板函数来说，参数必须是按照通用模板的定义来写的（包括个数、类型和顺序），但对于模板类来说，则没有任何要求，我们可以写一个跟通用模板压根没什么关系的一种特化，比如说：
```cpp
template <typename T>
struct Test { // 通用模板中有2个成员变量，1个成员函数
  T a, b;
  void f();
};

template <>
struct Test<int> { // 特化的内部定义可以跟通用模板完全不同
  double m;
  static int ff();
}
```
- 偏特化
偏特化的模板本质上还是模板，它仍然需要编译期来根据需要进行实例化的，所以，在链接方式上来说，全特化要按普通函数/类/变量来处理，而偏特化模板要按模板来处理。先明确一个点：模板函数不支持偏特化，因此偏特化讨论的主要是模板类。
```cpp
#include <iostream>

template <typename T1, typename T2>
struct Test {
};

template <typename T>
struct Test<int, T> {
  static void f();
};

template <typename T>
void Test<int, T>::f() {
  std::cout << "part specialization" << std::endl;
}

void Demo() {
  Test<int, int>::f(); // 按照偏特化实例化，有f函数
  Test<int, double>::f(); // 按照偏特化实例化，有f函数
  Test<double, int>::f(); // 按照通用模板实例化，不存在f函数，编译报错
}
```
如果偏特化和全特化同时存在呢？
先说答案，上面的实例会按照【2】的方式，也就是直接调用全特化。大致上来说，全特化优先级高于偏特化，偏特化高于通用模板。
对于函数来说，模板函数不支持偏特化，但支持重载，并且重载的优先级高于全特化。比如说：
```cpp
void f(int a, int b) {} // 重载函数

template <typename T1, typename T2>
void f(T1 a, T2 b) {} // 通用模板

template <>
void f<int, int>(int a, int b) {} // 全特化

void Demo() {
  f(1, 2); // 会调用重载函数
  f<>(1, 2); // 会调用全特化函数f<int, int>
  f(2.5, 2.6); // 会用通用模板生成f<double, double>
}
```
有的资料会管下面这种特化叫做「模式特化」，用于区分普通的「部分特化」。但它们其实都属于偏特化的一种，因为偏特化都是相当于特化了参数的范围。
```cpp
template <typename T>
struct Tool {}; // 这是另一个普通的模板类

template <typename T>
struct Test {}; // 【0】通用模板

template <typename T>
struct Test<Tool<T>> {}; // 【1】偏特化

void Demo() {
  Test<int> t1; // 使用【0】实例化Test<int>
  Test<Tool<int>>; // 使用【1】实例化Test<Tool<int>>
  Test<Tool<double>>; // 使用【1】实例化Test<Tool<double>>
}
```
##### 四 特化模板的优先级匹配
偏特化模板匹配的原则就是「特化程度更高者优先」，如果遇到可以同时命中多种的时候，将会报错（除非有更加匹配的特化，或者有对应的全特化，那么它会优先）。
匹配时更关注的是参数的「形式」，而非个数
```cpp
template <typename T1, typename T2, typename T3>
struct Test {}; // 【0】

template <typename T1, typename T2>
struct Test<T1, T2, int> {}; // 【1】

template <typename T>
struct Test<int, int, T> {}; // 【2】

void Demo() {
  Test<int, int, int> t; // 匹配哪个？
}
//这里报错
//Ambiguous partial specializations of 'Test<int, int, int>'
```

##### SFINAE
编译器在实例化模板时，如果遇到多个同名模板，则会逐一「尝试」匹配，在这个过程中如果发生了失败，并不会马上报错，因此把这种特性称之为「匹配失败不是错误（Substitution Failure Is Not An Error，简称SFINAE）」。
```cpp
template <typename T, bool Cond>
struct EnableIf {};

template <typename T>
struct EnableIf<T, true> {
  using type = T;
};

template <typename T>
void f(typename EnableIf<T, sizeof(T) <= sizeof(void *)>::type t) {
  std::cout << 1 << std::endl;
}

template <typename T>
void f(typename EnableIf<T, (sizeof(T) > sizeof(void *))>::type const &t) {
  std::cout << 2 << std::endl;
}

void Demo() {
  f<int>(1); // 打印1
  
  Test t;
  f<Test>(t); // 打印2
}
```
所谓的「匹配」就是指，编译器会拿着实参去尝试实例化，比如，实例化f<int>的时候，编译器会先尝试用第一个模板函数来实例化.然后这里的判断条件是符合的，所以替换为true.这时会去实例化EnableIf<int, true>，命中了它的偏特化，里面是有type的，而typename EnableIf<int, true>::type就是int，所以这里就变成了`void f(int t);`

接下来实例化EnableIf<Test, false>，没有命中偏特化，因此要用通用模板来实例化。但EnableIf<Test, false>中并没有type这个成员。因此，typename EnableIf<Test, false>::type这个表达就是个错误的表达，无法用它来实例化。我们把这个过程称之为「匹配失败（Substitution Failure）」。
注意，重点来了！！虽然匹配失败了，但这时编译器并不会立刻报错，而是会继续尝试匹配其他的模板，因为我们还有一个模板函数f还没尝试呢！于是，编译器会继续用第二个模板尝试实例化.于是按照这个模板进行实例化，函数原型是：void f<Test>(Test const &t)。

**手撸一些元编程工具**
参考代码在effective_c++/stl/中。
##### 模板元编程两大要素
**什么是模板元编程**
从这个模板元的元老中可以看出，它有2个要素，一个是用于静态判断的cond，另一个是用于类型处理的T。所以，模板元编程无非就是做两件事，一个是静态数学计算（包括了布尔类型的逻辑运算和整数类型的数值运算。这里的「静态」是指编译期行为。）；另一个是类型处理（type traits，也被翻译为「类型萃取」）。
所以，静态计算和类型处理的编写过程，就称为「模板元编程」。把这两个要素的结果放到enable_if（或类型行为的模板）中，再通过SFINAE特性生成需要的代码再去参与编译。
强调一下，模板元编程是完完全全的编译期行为，任何设计运行期才能确定的数据都不可用，因此我们的编程思维跟普通代码编写的思维也是完全不同的，请读者一定要注意。
**两个要素**
静态计算和类型处理
##### 静态计算
静态计算主要有整数运算（C++20起也支持浮点数运算了）和逻辑运算。其中逻辑运算是重点，也是我们在模板元编程中最常用到的静态计算。下面分别来介绍。
https://blog.csdn.net/fl2011sx/article/details/128800210
静态计算：整数运算，逻辑运算
实例已经整理到了在effective_c++/stl/中。
value也是STL中约定的命名方式，原则上可以不遵守，但倡导大家来遵守。value表示的就是这个辅助类的值，既然这个辅助类的作用是「静态处理」，那么自然要输出一个值。

##### 类型处理
模板元编程的另一要素便是类型处理，英文叫type traits，所以也被翻译为「类型萃取」。其实这里的「萃取」并没有多么高大上的意思，类比前面章节介绍的「数值计算」，数值计算的结果应该是一个数值，而类型处理的结果就应该是个类型。
https://blog.csdn.net/fl2011sx/article/details/128831824
实例已经整理到了在effective_c++/stl/中。
type也是STL中约定的命名方式，原则上可以不遵守，但倡导大家来遵守。type表示的就是这个辅助类的输出，既然这个辅助类的作用是「类型处理」，那么自然要输出一个类型。
**推导规则**
https://zhuanlan.zhihu.com/p/420138672
**类模板参数类型推导指南**
https://blog.csdn.net/janeqi1987/article/details/100211442

##### 函数类型处理
declval需要好好了解一下。
在类型变换中，我们是没有实际数据的，换句话说，不会真的去定义一个T类型的变量，而仅仅是需要它来参与类型的变换。
为了解决这个「仅需要类型，而不想做构造检测」的问题。
STL中就提供了declval工具，用来避开构造检测而生成一个纯类型的对象,它不是真正的生成对象，
```cpp
struct Test {
  Test(int); // 没有无参构造
  void method();
};

template <typename T>
struct XXX {
  using type = decltype(declval<T>().method()); // 这样就不会构造失败了
  //using type = decltype(T{}.method()); // 这里构造T{}的时候会失败,因为要调用无参构造函数，但是Test并没有无参构造函数。
};
```
然后关于判断类型中是否含有某个成员的的方法，值得好好阅读。
https://blog.csdn.net/fl2011sx/article/details/128864369，

##### 实现一个动态的get
采用编译器展开的方法。叫做「编译期展开」，也就是在编译期枚举出运行时可能传入的所有数据，分别生成对应的代码指令，然后当运行期数据确定的时候去执行对应的指令。
https://blog.csdn.net/fl2011sx/article/details/128933496

##### 多选一结构
std::variant的简化版本
https://borehole.blog.csdn.net/article/details/128967835

##### 通过类型访问
访问器
https://borehole.blog.csdn.net/article/details/129024453

##### 访问函数
std::visit
https://borehole.blog.csdn.net/article/details/129041001


##### 对比一下面向对象编程VS模板编程VS函数式编程
https://borehole.blog.csdn.net/article/details/129041001
详细体验过模板元编程理念和方法之后，我们要再来介绍一下C++的多范式。虽然一开始C++是为了给C语言扩充以适配OOP（面相对象编程）范式的，但后来成熟了的C++语言本身开放性很足，因此能够使用多种编程范式。同时又因为STL本身并没有使用OOP范式，而是把模板玩出了花，因此「模板范式」在C++中也有了弥足轻重的地位。
所谓「模板范式」，其核心理念就是「在编译期，确定尽量多的事情」。也就是说，它倾向于把更多的工作交给编译期来完成，以减少程序运行时期的不确定因素。
面向对象方法
```cpp
// 协议类
class TableViewDataSource {
 public:
  virtual std::string GetData() const = 0;
};

// 使用者
class TableView {
  public:
   void SetDataSource(TableViewDataSource *data_source);
   void GetData(){
		if (data_source_ != nullptr) {
  			auto data = data_source_->GetData();
			return data;
		}
   }

  private:
   TableViewDataSource *data_source_;
};
class HttpRequest : public SocketReq, public TableViewDataSource {
 public:
  ... // 一些自己的方法
  // 实现协议类方法
  std::string GetData() const override;
};
void Demo() {
  HttpRequest hr;
  TableView tv;
  tv.SetDataSource(&hr);
  tv.GetData();
}
```
模板编程
```cpp
// 用于判断类型T中是否含有GetData方法
template <typename T, typename V = std::string>
struct IsDataSource : std::false_value {};

template <typename T>
struct IsDataSource<T, std::void_t<decltype(std::declval<T>().GetData())>> : std::true_value {};

class TableView {
 public:
  template <typename DataSource>
  std::enable_if_t<IsDataSource<DataSource>::value, std::string>
  GetData(DataSource *data_source) const {
    return data_source->GetData();
  };
}
// 不需要多继承，不会改变继承链
class HttpRequest : public SocketReq {
 public:
  ... // 一些自己的方法
  // 实现数据源方法，不需要虚函数
  std::string GetData() const;
};

// 使用时
void Demo() {
  HttpRequest hr;
  TableView tv;
  tv.GetData(&hr); // hr、tv中都不携带虚函数表，如果hr的类型不符合要求，编译期就直接会被拦截
}
```
函数式编程
```cpp
class TableView {
 public:
  void SetDataSource(std::function<std::string()> func) {
    get_data_func_ = func;
  }
  std::string GetData() const {
    return get_data_func_();
  };

 private:
  std::function<std::string()> get_data_func_;
};

class HttpRequest : public SocketReq {
 public:
  std::string GetData() const;
};

void Demo() {
  TableView tv;
  HttpRequest hr;
  
  tv.SetDataSource(std::bind(&HttpRequest::GetData, &hr)); // 脱离数据源对象实体，直接把函数传进去
  tv.GetData(); 
}
```

*总结一下模板自动类型推导*
*在网上找找Effecti C++和More Effective C++的哪些条款已经不适用现代C++语法了。更新一下笔记*

### 函数式编程
lamdba编程。

### 面向过程编程，函数式编程，模板元编程，面向对象编程，泛型编程，宏编程。
C++中分别在什么时候使用这三种语法？
预处理期：
宏编程，C中比较普遍。它跟C++的模板元编程的作用相当。都是在运行期之前进行计算以生成代码。
编译期：
模板元编程，主要是要将运行期的计算放到编译期来进行，此外它是实现STL的基石。如果想对面向对象进一步抽象就需要模板编程。
运行期：
面向过程编程，例如C语言。适合做一些底层业务，驱动，嵌入式领域。跟底层打交道。不适合现实世界业务领域(比如：售票系统)。
面向对象编程，适合解决领域业务问题，比如外包。它可以将现实世界的各种元素抽象成为类。
泛型编程，是将类型参数化，STL的使用就是泛型编程。STL的实现依赖于模板元编程。
函数式编程，它更适合做科学计算，大数据中的流式处理。不适合将现实世界的领域问题(比如：售票系统)映射到函数式编程的范式中。

### STL编程(模板编程)语法
*进阶需要阅读《Effective STL》，已经下载到文档中了。*

#### 六大组件
STL 提供了六大组件，彼此组合套用协同工作。这六大组件分别是：
容器（Containers）：各种数据结构，如 vector、list、deque、set、map 等。从实现的角度来看，容器是一种 class template。
算法（Algorithms）：各种常用算法，提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作，比如 sort、search、copy、erase。从实现的角度来看，STL 算法是一种 function template。
迭代器（Iterators）：迭代器用于遍历对象集合的元素，扮演容器与算法之间的胶合剂，是所谓的“泛型指针”，共有 5 种类型，以及其他衍生变化。从实现角度来看，迭代器是一种将 operator*、operator->、operator++、operator-- 等指针操作予以重载的 class template。所有的 STL 容器附带有自己专属的迭代器，因为只有容器设计者才知道如何遍历自己的元素。
仿函数（Functors）：也称为函数对象（Function object），行为类似函数，可作为算法的某种策略。从实现角度来看，仿函数是一种重载了 operator() 的 class 或者 class template。
适配器（Adaptors）：一种用来修饰容器或者仿函数或迭代器接口的东西。例如 STL 提供的 queue 和 stack，就是一种空间配接器，因为它们的底部完全借助于 deque。
分配器（Allocators）：也称为空间配置器，负责空间的配置与管理。从实现的角度来看，配置器是一个实现了动态配置空间、空间管理、空间释放的 class template。
详细介绍参考https://zhuanlan.zhihu.com/p/664872204

#### 代码示例
C++ STL容器用法示例大全
https://blog.csdn.net/lady_killer9/article/details/81175682





### 其他
#### 为了方便测试，子进程的输出如何输出到父进程的控制台中？
通过命令`ll /proc/<pid>/fd`可以查看某个进程的标准输入输出被定向到了哪个设备。0,1,2。分别代表标准输入，标准输出，标准错误。
可以直接 tail或cat，来查看/proc/<pid>/fd/1 某个进程的标准输出。

Linux: 进程标准输入输出设备描述符
https://blog.csdn.net/weixin_42262944/article/details/131139105

实际上无论前台后台，都是先输出到一块指定的内存区域，再由系统视情况将全部或一部分输出到各种外部设备。默认状态下，这块内存区域是标准输出流，外部设备是显卡的帧缓冲。
你也可以把输出定向到/dev/null之类的设备，或者磁盘文件。
https://www.zhihu.com/question/23400948
这个属于IPC的知识范畴了,关键是使用pipe和dup2这两个函数,子进程通过dup2把stdout,stderr重定向到pipe的write端，父进程从pipe的read端取就行了。
```c
int pipefd[2];
	pid_t cpid;
	char buf;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string> which is one seperated char\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {    /* Child writes to pipe[1]*/
		close(pipefd[0]);          /* Close unused read end */
		dup2(pipefd[1],1);
		execl("/bin/ls", "/bin/ls", (char *) NULL);

	} else {            /* Parent reads from pipe[0]  */
		wait(NULL);                /* Wait for child */

		close(pipefd[1]);          /* Close unused write end */
		while (read(pipefd[0], &buf, 1) > 0){
			if(write(STDOUT_FILENO, argv[1], 1)!=1){
				perror("write failed");
				exit(EXIT_FAILURE);
			}
			if(write(STDOUT_FILENO, &buf, 1)!=1){
				perror("write failed");
				exit(EXIT_FAILURE);
			}
		}
		if(write(STDOUT_FILENO, "\t", 1)!=1){
			perror("write failed");
			exit(EXIT_FAILURE);
		}

		close(pipefd[0]);
	}

	return 0;
```
#### clang 用法
1. 生成汇编代码
`clang -S -fobjc-arc Animal.cc -o Animal.s`

2. 生成IR,IR相对汇编要好容易看一点。这里可以看到生成中间码，是否单独定义了某个函数，如果是非内联函数可以被看到。如果是内联函数且没有被调用，则可能被优化掉。
`clang -emit-llvm -S -c Animal.cc -o Animal.ll`

3.
执行此命令可以查看`clang -Xclang -ast-dump -c 05.cpp`源代码的AST结构。
在AST结构中可以查看到C++默认生成了哪些成员函数。
CXXConstructorDecl和CXXMethodDecl，代表构造函数声明和其他默认成员函数的声明。
```shell
|-CXXRecordDecl 0x7fb94385d6a8 <./../../include/effective_c++/05.hpp:1:1, line:10:1> line:1:7 referenced class Empty definition
| |-DefinitionData pass_in_registers empty aggregate standard_layout trivially_copyable pod trivial literal can_const_default_init
| | |-DefaultConstructor exists trivial defaulted_is_constexpr
| | |-CopyConstructor simple trivial has_const_param implicit_has_const_param
| | |-MoveConstructor exists simple trivial needs_implicit
| | |-CopyAssignment trivial has_const_param implicit_has_const_param
| | |-MoveAssignment exists simple trivial needs_implicit
| | `-Destructor simple irrelevant trivial needs_implicit
| |-CXXRecordDecl 0x7fb94385d7b8 <col:1, col:7> col:7 implicit class Empty
| |-CXXConstructorDecl 0x7fb94385da40 <col:7> col:7 implicit used Empty 'void () throw()' inline default trivial
| | `-CompoundStmt 0x7fb94385dd08 <col:7>
| |-CXXConstructorDecl 0x7fb94385db68 <col:7> col:7 implicit used Empty 'void (const Empty &) throw()' inline default trivial
| | |-ParmVarDecl 0x7fb94385dc78 <col:7> col:7 'const Empty &'
| | `-CompoundStmt 0x7fb94385de50 <col:7>
| `-CXXMethodDecl 0x7fb94385df18 <col:7> col:7 implicit used operator= 'Empty &(const Empty &) throw()' inline default trivial
|   |-ParmVarDecl 0x7fb94385e018 <col:7> col:7 'const Empty &'
|   `-CompoundStmt 0x7fb94385e158 <col:7>
|     `-ReturnStmt 0x7fb94385e148 <col:7>
|       `-UnaryOperator 0x7fb94385e130 <col:7> 'Empty' lvalue prefix '*' cannot overflow
|         `-CXXThisExpr 0x7fb94385e120 <col:7> 'Empty *' this
```

