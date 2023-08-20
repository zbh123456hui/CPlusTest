#include <iostream>

using namespace std;

//父类1
class Base1{
public:
    virtual void f(){ cout<<"Base1::f()"<<endl; }
    virtual void g(){ cout<<"Base1::g()"<<endl; }
};

//父类2
class Base2{
public:
    virtual void h(){ cout<<"Base2::h()"<<endl; }
    virtual void i(){ cout<<"Base2::i()"<<endl; }
};

class Derive:public Base1,public Base2{
public:
    virtual void f(){ cout<<"Derive::f()"<<endl; }  //只覆盖Base1的f
    virtual void i(){ cout<<"Derive::i()"<<endl; }  //只覆盖Base2的i

    //如下三个是本类自己的虚函数
    virtual void mh(){ cout<<"Derive::mh()"<<endl; }
    virtual void mi(){ cout<<"Derive::mi()"<<endl; }
    virtual void mj(){ cout<<"Derive::mj()"<<endl; }
};

int main(){
    cout<<sizeof(Base1)<<endl;
    cout<<sizeof(Base2)<<endl;
    cout<<sizeof(Derive)<<endl;
    Derive ins;  //定义一个子类对象
    Base1& b1=ins;
    Base2& b2=ins;
    Derive& d=ins;

    typedef void(*Func)(void);

    long* pderived1=(long*)(&ins);
    long* vptr1=(long*)(*pderived1);

    long* pderived2=pderived1+1;
    long* vptr2=(long*)(*pderived2);

    //Func f1=(Func)vptr1[0];
}