#include <iostream>

using namespace std;

class Grand{      //爷爷类
public:
    int m_grand;
};

class A1:virtual public Grand{
public:
    int m_a1;
};

class A2:virtual public Grand{
public:
    int m_a2;
};

class C1:public A1,public A2{
public:
    int m_c1;
};

int main(){
    cout<<sizeof(Grand)<<endl;
    cout<<sizeof(A1)<<endl;
    cout<<sizeof(A2)<<endl;
    cout<<sizeof(C1)<<endl;
}
//使用virtual，输出4、16、16、40
//不使用virtual，输出4，8，8，20