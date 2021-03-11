# 可变参数列表

```c
#include <stdio.h>
#include <stdarg.h>
void printer(const int num, ...)
{
    va_list args;
    va_start(args, num);
    printf("%d\n", va_arg(args, int));
    printf("%d\n", va_arg(args, int));
    printf("%d\n", va_arg(args, int));
    va_end(args);
}
int main()
{
    printer(3, 2, 3, 5);//2 3 5
}

```

#### va_list

数据类型，实际上为char*，指向参数列表的指针

#### va_start(va_list args, param)

将va_list指针指向param后一个参数

#### va_arg(va_list args, type)

返回当前指针指向参数的值，然后指针后移

#### va_end(va_list args)

指针置0，函数退出前必须调用

# 面试

### #与##在编译时的作用？

```c
//#是把宏参数转化为字符串的运算符
//##是把两个宏参数连接的运算符，注意##并不将参数转化为字符串
#define STR(arg) #arg
#define CON(a,b) a##b

int main(){
    printf("%s\n", STR(AAAA));//AAAA
    int AABB = 9;
    printf("%d\n", CON(AA,BB));//9
}
```

### extern关键字

作用1：告诉该变量或函数可能在其他文件内被定义，编译器可以去其他文件寻找定义。但非要在本文件内定义也没问题。

作用2：extern "C"，当C++编译器编译extern "C"块内内容时会以C的编译方式产生改内容的目标文件，就不会在链接阶段出问题；如果没有这个，且C++编译了该文件产生的目标文件内，函数的名字是被打乱的，当C编译器链接该目标文件时就会出错。

```c
//单一语句
extern "C" void func();
//复合语句
extern "C"{
    void func1();
    void func2();
}
//包含头文件
extern "C"{
    #include<head.h>
}
```

##### 注意事项：extern "C"不能写在函数内部

### 结构体位域

```c
//注意：
//位域不能跨字节

```

