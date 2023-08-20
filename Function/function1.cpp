#include <iostream>

using namespace std;

class MYACLS{
public:
    int m_i;
    void myfunc(int abc){
        m_i+=abc;
    }
    virtual void myvirfun2(){
    //虚函数在内存中有一个固定的地址，是在编译时确定好的。
        printf("myvirfunc2()被调用，this=%p\n",this);
    }
    virtual void myvirfun(){
        printf("myvirfunc()被调用，this=%p\n",this);
        myvirfun2();             //通过虚函数表实现
        MYACLS::myvirfun2();     //直接调用，更有效率
    }
};

//全局函数gmyfunc
void gmyfunc(MYACLS* ptmp,int abc){
    ptmp->m_i+=abc;
}

int main(){
    MYACLS myacls;
    myacls.myfunc(18);      //调用成员函数
    gmyfunc(&myacls,18);    //调用全局函数
    //C++设计的时候有一个要求：对普通成员函数的调用不应该比对全局函数的调用效率差。
}