# Tips

## 内存分配

| 项     | 解释                                                     |
| ------ | -------------------------------------------------------- |
| 方法区 | 也就是代码区，存放函数体的二进制形式。特点：共享，只读。 |
| 全局区 | 存放全局变量、静态变量、字符串常量和全局常量。           |
| 栈     | 存放函数参数、局部变量、局部常量。由编译器自动管理。     |
| 堆     | 程序员自行分配。                                         |

### 空对象占用

```c++
//空对象占用1Byte，为了有一个独一无二的地址区分空对象“们”。
class A{};
A a;//sizeof(a)结果为1
```

## 函数相关

### 声明与定义有默认值的函数

```c++
//函数声明和函数定义，默认值只能在其中一个实现。
//建议实现方式
void func(int a = 10,int b = 10);
void func(int a,int b){
    return a+b;
}
//或者
void func(int a,int b);
void func(int a=10,int b=10){
    std::std::cout<<a+b;
}
```

### 占位参数也能有默认值

```c++
//函数参数占位参数也能有默认值。
void func(int a,int = 10);
```

### 函数重载

#### 重载参数中的引用参数

```c++
//重载参数里面有引用与引用常量时的调用选择
void fun(int &a);
void fun(const int &a);

int a = 10;
const int b = 10;
const int &c = a;

fun(a);//调用fun(int &a);
fun(b);fun(c);fun(10);//调用fun(const int &a);
```

#### 运算符重载

##### 重载方式

有成员函数重载和全局函数重载两种方法。

##### 左移运算符重载

```c++
//左移运算符重载一般用于自定义输出，
//而且由于必须实现std::cout在左侧，该函数必须定义为友元并实现为全局函数
class A{
    friend ostream& operator<<(ostream& std::cout, A a);
    private:
    	int n;
};
ostream &operator<<(ostream &std::cout, A a){
    std::cout << "a=" << a.n;
    return std::cout;
}
```

##### 递增运算符重载

```c++
//区分前置和后置的方法为占位参数
class A{
public:
    A &operator++(){
        this->n++;
        return *this;//返回引用方便链式调用
    }
    A operator++(int){//占位参数区分前后置
        A *tmp = this;
        this->n++;
        return *tmp;//后置递增重载函数返回值不返回引用，因为tmp是一个局部对象，同时自然无法链式，不过后置递增链式调用本身不被需要。
    }
private:
    int n;
};
```

##### 赋值运算符重载

```c++
class A{
    public:
    	A(int a){
            n = new int(0);
        }
    	~A(){
            if(n != NULL){
                delete n;
                n = NULL;
            }
        }
		A &operator=(A &b){//返回引用方便链式调用
        	if(n != NULL){
           		delete n; 
                n = NULL;
        	}
            n = new int(*b.n);
            return *this;
    	}
    private:
    	int *n;
};
```

##### 关系运算符重载

```c++
class A{
    public:
    	bool operator==(A &a){//注意返回值为bool就行
            if(n == a.n)return true;
            return false;
        }
    private:
    	int n;
};
```

##### 函数调用运算符重载

```c++
//函数调用运算符重载，又称仿函数
class A{
    public:
    	operator()(int a){
            std::cout << "param:" << a << std::endl;
        }
};

A a;
a(7);//使用方法
A()(7);//使用方法,A()相当于一个匿名对象
```

### 函数内声明函数

```c++
//函数内能写另一个函数的声明。
void fun(){
    void fun1();
}
```

## 构造与析构

### 匿名对象注意

```c++
//匿名对象不要使用显示构造方法，编译器会将其认作一个对象创建，这就是失去了匿名对象的本意。
class Person{
    ...
};

Person(p);//该句等价于下一句
Person p;
```

### 拷贝构造函数使用情景

```c++
Person p2(p1);//1.拷贝构造对象

void fun(Person p);//2.值传递

Person fun(){
    Person p;
    return p;
}//3.值方式返回局部对象
```

### 类的默认函数

默认情况下编译器提供四个函数：无参构造、无参析构、拷贝构造和赋值运算符。除非自己实现拷贝构造，不然编译器会自己提供，即使已经自己实现了有参或无参构造函数。

### 深拷贝与浅拷贝

| 项     | 例子                                                         |
| ------ | ------------------------------------------------------------ |
| 深拷贝 | 自己实现拷贝构造函数，为指针类型单独开辟内存。               |
| 浅拷贝 | 值拷贝，当对象内有指针类型数据并在析构函数中释放，这种拷贝方式会出现多次释放同一内存的错误。 |

### 类内对象与构造顺序

```c++
//当类中有其他类对象成员时，先执行类内对象的构造函数。
//创建B的实例时，B的构造函数晚于A的构造函数
class A{};
class B{
  A a;  
};
```

# 类与对象

## this指针

### this指针含义

this指针隐含于每个类内非静态成员函方法，指向调用该方法的对象。

this指针是一个指针常量，无法修改其指向的对象。

### this指针用于链式调用

```c++
Person A(){
public:
    Person& AddNum(int num){//注意，为了链式调用一定要返回引用
        this.num += num;
        return *this;
    }
    Person(int n):num(n){}
private:
    int num;
};

A a(1);
a.AddNum(1).AddNum(2);
```

### 常函数、常对象、this指针与mutable

```c++
class A{
    public:
	    void fun1(){
            this = NULL;//错误，A* const this无法执行此操作
        }//普通成员函数内隐含的this指针是指针常量，即：A* const this; 
    	void fun2() const {
            this -> num1 = 1;//错误，const A *this无法执行此操作
            this -> num2 = 1;//正确，mutable特殊标志
        }//常函数后的则是修饰this，使得在函数内无法修改this指向的值，即：const A* const this;
    private:
    	int num1;
    	mutable int num2;
};
const A a;
a.num1 = 100;//错误，常对象无法修改内部成员值
a.num2 = 100;//正确，mutable特殊标志
a.fun1();//正确
a.fun2();//错误，常对象只能调用常函数
```

### 空指针调用成员函数

```c++
//对象的空指针可以调用对象成员函数，前提是该成员函数没有访问到对象内部成员。
class A{
    public:
    	Print(){std::cout << "A class print func";}
    	PrintNum(){std::cout << num;}
    private:
    	int num;
};

A* a = NULL;
a->Print();//正确
a->PrintNum();//错误
```

## 友元

### 含义

友元即让一个函数或类访问到另一个类的私有成员

### 友元三种实现方式

```c++
//以下实现对象可用指针，可用对象本体
//友元函数
class A{
    friend void FriendFunc(A a);
private:
    int paval = 1;
};
void FriendFunc(A a){
    a.paval = 10;
}

```

```c++
//友元类
class B;
class A{
    friend class B;
private:
    int paval = 1;
};
class B{
    public:
        void SetPaval(A a){
            a.paval = 10;
        }
};
```

```c++
//成员函数做友元
class A;
class B{
    public:
        void SetPaval(A a);
};
class A{
    friend void B::SetPaval(A a);
private:
    int paval = 0;
};
void B::SetPaval(A a){
    a.paval = 10;
}
```



## 继承

### 同名成员访问

访问本类成员直接访问，访问父类成员加作用域

```c++
class A {
public:
	int a = 0;
	void fun() { std::cout << "A\n"; }
};
class B : public A {
public:
	int a = 1;
	void fun() { std::cout << "B\n"; }
};

B b;
std::cout << b.a << "\n" << b.A::a << std::endl;//1 0
b.fun();//B
b.A::fun();//A
```

### 子类父类同名成员函数

如果子类有与父类同名的函数，会隐藏所有父类同名函数，即使该函数在父类有重载操作

### 静态成员同名

```c++
//操作与非静态成员一致，不过多了下面这种访问方式
B::A::a;
B::A::fun();
```

### 多继承注意事项

多继承可能引起父类成员同名，需要添加作用域加以区分，所以不建议在开发中使用多继承。

### 菱形继承与虚继承

```c++
class A {
public:
	int32_t val;
};
class B :public A {
};
class C :public A {
};
class D :public B, public C {
};
//问题1：如果我们需要两份val，D中有两个val，如何区分？
//解决办法：使用作用域（如下）
D d;
d.B::val = 1;
d.A::val = 1;
```

```c++
//问题2：我们只需要一份val，怎么办？
//解决办法：虚继承（如下）
class A {//虚基类
public:
	int32_t val;
};
class B :virtual public A {//虚继承，sizeof(B)=8,vbptr+val=4+4
};
class C :virtual public A {//虚继承
};
class D :public B, public C {//sizeof(D)=8,vbptr*2+val=4+4
};
//此时的内存模型：B和C中分别存储一个虚基类表指针vbptr指向虚基类表，其记录了虚基类与本类的偏移地址，当D实例访问val时使用偏移量计算地址，然后根据地址在虚基类表（不占用类对象存储空间）得到A中的val地址，由此访问到唯一的A中的val
```

## 多态

多态分为静态多态和动态多态。

静态多态是指函数地址早绑定的，编译阶段就确定了。如函数重载。

动态多态是指函数地址晚绑定的，运行阶段才确定。

### 动态多态

使用父类指针指向子类对象实例，子类重写父类虚函数实现多态。

```c++
class A {
public:
	virtual void Work() { std::cout << "A\n"; }
	virtual ~A() {}//这一行是为了什么？
};
class B:public A {
public:
	void Work() { std::cout << "B\n"; }
};
class C :public A {
public:
	void Work() { std::cout << "C\n"; }
};

A *a = new B;
a->Work();//B
delete a;
```

### 虚析构函数

在实现动态多态时往往要在父类实现一个虚析构函数，因为我们使用的是父类指针，析构时是去寻找父类析构函数，而我们创建的是一个子类实例，这个时候就会发生内存泄漏。如果我们实现了父类虚析构函数，析构时就会先执行子类析构函数再去执行父类析构函数。

### 动态多态的实现：虚函数表

在有虚函数（纯虚函数包括在内）的类实例中存放着一个虚函数表指针vfptr指向该实例的虚函数表，其中包含该实例所有虚函数地址。上例中，A实例vfptr指向的表就包含A::work, A::dtor（代表析构函数），B实例vfptr指向的表包含B::work, B::dtor。

注意：如果子类不重写父类虚函数，那么子类的虚函数表内存放的虚函数地址就是指向父类虚函数的。

### 纯虚函数

有至少一个纯虚函数的类称作抽象类，抽象类无法实例化，且纯虚函数除非是析构函数，否则无须实现，纯虚析构函数必须实现。

# 模板

## 模板必须指定类型T才能使用

```c++
//即使模板参数没有被使用到，如果想要使用模板必须在<>指定数据类型
template<class T>
void print() {
	std::cout << "template\n";
}
print();//报错
print<int32_t>();//template
```

## 模板与自动类型转换

```c++
//模板不会发生自动类型转换，除非显示指定数据类型，这时模板会发生隐式自动类型转换
template<class T>
void print(T a,T b) {
	std::cout << a + b;
}

print(3.1, 5);//报错，类型不一致，因为模板不会自动类型转换
print<double>(3.1, 5);//8.1
```

## 模板函数与普通函数重载时的调用规则

```c++
//1.普通函数与模板都完美匹配时调用普通函数
//2.使用空模板参数时，强制调用模板函数
//3.其他情况调用模板函数
void print(int32_t a, int32_t b) {
	std::cout << "normal function\n";
}
template<class T,class E>
void print(T a,E b) {
	std::cout << "template\n";
}

print(5, 6);//normal function
print<>(5, 6);//template
```

## 模板函数特化

```c++
template<class T,class E>
void print(T a,E b) {
	std::cout << "template\n";
}
template<> void print(int32_t a, char b) {//写在模板后面
	std::cout << "int and char\n";
}
```

## 类模板与函数模板区别

```c++
//类模板没有类型自动推导，必须手动指定数据类型；
template<class T>
class A {
public:
	T val;
};

A<int32_t> a;
A b;//错误，不能类型自动推导。
```

```c++
//类模板在模板参数列表中可以有默认参数，且默认类型参数与普通函数参数一样需要从右往左写
template<class T=int32_t>
class A {
public:
	T val;
};

A<char> a;
A<> b;
A b;//仍然错误，需要使用上一行的方法实现
```

## 类模板成员函数在调用时才创建

```c++
//以下内容可以通过编译
class A{
public:
	void work() { std::cout << "A\n"; }
};
template<class T>
class B {
public:
	T obj;
	void work() { obj.work(); }//T的类型都没确定，去调用不知道是否存在的work函数却可以通过编译
};
```

## 类模板对象做函数参数

```c++
//1.指定传入类型
template<class T>
class A {
public:
	T val;
};
void printA(A<int32_t> &a) {
	std::cout << "A<int32_t> &a\n";
}

A<int32_t> a;
printA(a);
```

```c++
//2.参数模板化
template<class T>
class A {
public:
	T val;
};
template<class Type>
void printA(A<Type> &a) {
	std::cout << "A<" << typeid(Type).name() << "> &a\n";
}

A<int32_t> a;
printA(a);//A<int> &a
```

```c++
//3.整个类模板化
template<class T>
class A {
public:
	T val;
};
template<class Type>
void printA(Type &a) {
	std::cout << typeid(Type).name() << " &a\n";
}
A<int32_t> a;
printA(a);//class A<int> &a
```

## 类模板与继承

```c++
//子类继承模板类时必须实现父类模板参数
//当子类也实现为模板时，它也成为一个模板类
template<class T>
class A {};

class B :public A<int32_t> {};

template<class E,class K>
class C:public A<K>{};
```

## 类模板的类外实现

```c++
//类模板成员函数的类外实现与普通函数略有不同，需要使用模板声明，并且要在作用域后加上模板参数列表
template<class T>
class A {
	void work();
};
template<class T>
void A<T>::work() {
	cout << "working\n";
}
```

## 类模板分文件编写

```c++
//按普通的分文件编写形式可以通过编译，但是一使用到模板类就会报错。
//Template.h
template<class T>
class A{
	void work();
};
//Template.cpp
template<class T>
void A<T>::work() {
	std::cout << "working\n";
}

A a;
a.work();//报错：无法解析的外部命令
```

```c++
//解决方法1:使用到A类的文件中包含Template.cpp而不是Template.h
#include"Template.cpp"
A a;
a.work();//working
```

```c++
//解决方法2:把cpp和h文件内容写在一起，后缀名改为hpp
```

## 模板类带模板参数的友元函数类外实现

```c++
template<class T>
class A;//告诉下面print函数参数，class A是存在的。

template<class T>
void print(A<T> &at);

template<class T>
class A {
	friend void print<>(A<T>&);//告诉class A，print函数是一个模板函数
	T val = 0;
};
template<class T>
void print(A<T> &at){
	std::cout << at.val;
}
```



# 一些函数

## 容器for_each()遍历

```c++
void Func(int32_t val) {
	std::cout << val << std::endl;
}
int main() {
	std::vector<int32_t> v;
	v.push_back(10);
	v.push_back(33);
	std::for_each(v.begin(), v.end(), Func);
}
```

## String

```c++
assign();
append();
find();
rfind();
replace();
compare();
at();
insert();
erase();
substr();
```

## Vector

```c++
assian(beg, end);		//将[beg,end)内数据拷贝
assign(n, elem);		//拷贝n个elem
empty();				//判断容器是否为空
capacity();				//容器容量
size();					//容器元素个数
resize(int num);		//重置容器长度为num，以默认值填充空余位置，超出num部分删除
resize(int num, elem);	//重置容器长度为num，以elem填充空余位置，超出num部分删除
at(int idx);			//返回索引idx的元素
swap(vector v);			//容器互换
reserve(int len);		//预留len容量，分配内存但不初始化，所以没有初始化的地方不能访问，减少容器动态扩展操作
```

## Deque

```c++

```



### swap可用于收缩内存

```c++
std::vector<int32_t> v(100000, 10);
std::cout << v.capacity() << "\n";//100000

v.resize(3);
std::cout << v.capacity() << "\n";//100000,resize后容量浪费严重

std::vector<int32_t>(v).swap(v);//std::vector<int32_t>(v)构造以v为参数的拷贝构造函数构造了一个匿名对象，与v互换，随后匿名对象接受了容量为100000的v后生命周期结束，纯工具。
std::cout << v.capacity() << "\n";
```



# STL

STL分为六大组件：容器、算法、迭代器、仿函数、适配器、空间配置器

容器：数据结构，如vector、list、map

算法：算法，如sort、find、for_each

迭代器：缝合了容器和算法，沟通桥梁

仿函数：行为类似函数，函数调用运算符重载

适配器：修饰容器、仿函数或者迭代器

空间配置器：负责空间配置和管理

## 容器

容器分为序列式容器和关联式容器

序列式容器元素的存储顺序与元素值无关，以线性排列储存元素

关联式容器元素的存储顺序与元素值无关

### Vector

单端数组，可以动态扩展，扩展方式是找一块更大的内存空间拷贝源数据，释放源空间。

### Deque

双端数组，相对于vector提升了头部插入效率，访问元素逊于vector。

实现原理：开辟多片连续的内存空间，由一个中控器管理这些内存空间。

<img src="C:\Users\CR\OneDrive\LifeTips\Techniques\img\c++ Deque 1.jpg" alt="image-20210311155138070" style="zoom:70%;" />

map中存放的指针结构：

<img src="C:\Users\CR\OneDrive\LifeTips\Techniques\img\c++ Deque 2.jfif" alt="image-20210311155138070" style="zoom:55%;" />

# 面试题

