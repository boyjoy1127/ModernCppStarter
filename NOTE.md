ModernCppStarter项目中整理出来一个代码样例项目，将CGL、Modern EffectiveC++、EffectiveC++、More EffectiveC++的良好实践都整理进来。
*《深度探索C++对象模型》这本书详细讲解的了对象初始化、析构和内存布局，值得阅读*
书中的条款在项目中以注释的形式来搞。
以C++14作为规范

### 各个书籍已经阅读的部分
Effective C++：4,5,6,7,8,9,10,11,12,13,14,15,16,17,32,33,34,35,36,37,38,39,40.
More Effective C++：14,9,8,3,24,33.
Modern Effective C++：11,17,14,12,18,19,20,21,22.

### 面向对象编程，class示例。
(按照这个顺序阅读添加：Effective C++(2,3,4,5,6)、More EffectiveC++(5,6,7)、Modern EffectiveC++(3)、CGL、)

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



##### 哪些情况使用inline

##### 哪些情况使用const

##### 哪些情况下使用friend


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

3. **MoreEffective C++ 5**
- 谨慎定义类型转换函数。一个参数进行调用的构造函数应当加上 explicit。比如单参数构造函数和多个参数且有默认值的构造函数。
- 接受一个 std::initializer_list 作为参数的构造函数也应当省略 explicit, 
  以便支持拷贝初始化 (例如 MyType m = {1, 2};).（来自Google C++开源代码风格指南的3.2部分）

4. **Effective C++ 9**
不要在构造和析构函数中调用virtual函数,因为此过程调用的虚函数可能来自基类而不是派生类。

5. **派生类的默认构造函数的机制**
1、如果基类定义了不带参数的默认构造函数，则编译器为派生类自动生成的默认构造函数会调用基类的默认构造函数。
2、如果基类定义了拷贝构造函数，则编译器为派生类自动生成的拷贝构造函数同样会调用基类的拷贝构造函数。
3、如果基类定义了带参数的构造函数，派生类没有定义任何带参数的构造函数，则不能直接调用基类的带参构造函数，程序编译不通过。

6. **派生类的构造函数执行顺序**
按照继承顺序执行基类的构造函数，然后按定义顺序执行对象成员的构造函数。
1、调用基类构造函数。
顺序按照它们被继承时声明的顺序（从左向右）：Base2, Base1, Base3。
2、对初始化列表中的成员进行初始化。
顺序按照它们在类中定义的顺序：Base1 member1; Base2 member2; Base3 member3;。
对象成员初始化时自动调用其所属类的构造函数。由初始化列表提供参数。
3、执行派生类的构造函数体中的内容。

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
*在面向对象部分的信息整理完成后，再跟CGL对应章节核对一遍*

### 模板编程，模板示例



### STL编程，STL示例



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

