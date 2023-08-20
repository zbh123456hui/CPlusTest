#include <iostream>
//成员变量是包含在每个对象中的，占字节的。
//成员函数虽然写在类定义中，但成员函数不占类对象的字节空间。
using namespace std;

class A{
public:
    char a;
    int  b;
    float c;
public:
    void func(){};
};

int main(){
    A a;  //sizeof():返回一个对象所占的字节数字
//    a.a='a';
    int ilen=sizeof(a);     //等价于sizeof(A)，结果为8

    printf("ilen=%d\n",ilen);   //ilen=8
    return 0;
}