#include <iostream>
#include <deque>

using namespace std;

class A{
public:
    int m_i;
    A(int tmpv):m_i(tmpv){
        cout<<"A::A()构造函数执行"<<endl;
    }
    A(const A& tmpA){
        m_i=tmpA.m_i;
        cout<<"A::A()拷贝构造函数执行"<<endl;
    }
    ~A(){
        cout<<"A::~A()析构函数执行"<<endl;
    }
};

int main(){
    deque<A> mydeque;
    for(int i=0;i<5;++i){
        cout<<"------------------begin--------------"<<endl;
        mydeque.push_front(A(i));
        cout<<"------------------end----------------"<<endl;
    }
    for(int i=0;i<5;++i){
        cout<<"------------------begin2--------------"<<endl;
        mydeque.push_front(A(i));
        cout<<"------------------end2----------------"<<endl;
    }
    for(int i=0;i<mydeque.size();++i){
        cout<<"下标为"<<i<<"的元素的m_i值为："<<mydeque[i].m_i<<endl;
        printf("对象mydeque[%d]的地址为%p\n",i,&mydeque[i]);
    }
    return 0;
}