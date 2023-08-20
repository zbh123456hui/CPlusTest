//和书上说的不一致，有问题
#include <iostream>

using namespace std;

class Base{
public:
    virtual void f(){ cout<<"Base::f()"<<endl; }
    virtual void g(){ cout<<"Base::g()"<<endl; }
    virtual void h(){ cout<<"Base::h()"<<endl; }
};

class Derive:public Base{
public:
    void g(){ cout<<"Derive::g()"<<endl; }
};

int main(){
    cout<<sizeof(Base)<<endl;
    cout<<sizeof(Derive)<<endl;
    Derive* d=new Derive();
    long* pvptr=(long*)d;
    long* vptr=(long*)(*pvptr);
    for(int i=0;i<=2;i++){
        printf("vptr[%d]=0x:%p\n",i,vptr[i]);
    }
}