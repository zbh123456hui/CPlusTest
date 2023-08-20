#include <iostream>

using namespace std;

class A{
public:
    int i;            //一个成员变量，4字节
    virtual void testfunc(){}   //虚函数
};

int main(){
    A a;
    int ilen=sizeof(a);
    cout<<ilen<<endl;
    char* p1=reinterpret_cast<char*>(&a);  //0xfe9ddffc38类型转换，属于硬转，a是对象
                                            //首地址
    char* p2=reinterpret_cast<char*>(&(a.i));//0xfe9ddffc30
    cout<<"p1:"<<&p1<<endl;
    cout<<"p2:"<<&p2<<endl;
    if(p1==p2){
        cout<<"虚函数表指针位于对象内存的末尾"<<endl;
    }else{
        cout<<"虚函数表指针位于对象内存的开头"<<endl;
    }
}
//虚函数表指针位于对象内存的起始（上面开头）位置。