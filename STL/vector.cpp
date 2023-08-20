#include <iostream>
#include <vector>

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
    vector<A> myveca;
    cout<<"myveca.capacity()="<<myveca.capacity()<<endl;
    cout<<"myveca.size()="<<myveca.size()<<endl;
    myveca.reserve(10);    //为容器预留空间，前提是知道该容器最多会容纳多少元素
    cout<<"myveca.size()="<<myveca.size()<<endl;
    cout<<"myveca.capacity()="<<myveca.capacity()<<endl;
    for(int i=0;i<5;++i){
        cout<<"--------------begin--------------------"<<endl;
        cout<<"容器插入元素之前size="<<myveca.size()<<endl;
        cout<<"容器插入元素之前capacity="<<myveca.capacity()<<endl;
        myveca.push_back(A(i));
        cout<<"容器插入元素之后size="<<myveca.size()<<endl;
        cout<<"容器插入元素之后capacity="<<myveca.capacity()<<endl;
        cout<<"---------------end---------------------"<<endl;
    }
    cout<<"打印一下每个元素的地址看看----------------"<<endl;
    for(int i=0;i<5;++i){
        printf("下标为%d的元素的地址是%p，m_i=%d\n",i,&myveca[i],myveca[i].m_i);
    }
    cout<<"删除一个元素看看-----------------"<<endl;
    int icount=0;
    for(auto pos=myveca.begin();pos!=myveca.end();++pos){
        icount++;
        if(icount==2){            //删除m_i==1
            myveca.erase(pos);
            break;
        }
    }
    for(int i=0;i<4;++i){
        printf("下标为%d的元素的地址是%p，m_i=%d\n",i,&myveca[i],myveca[i].m_i);
    }
    cout<<"再次插入一个元素看看-----------------"<<endl;
    icount=0;
    for(auto pos=myveca.begin();pos!=myveca.end();++pos){
        icount++;
        if(icount==2){            //删除m_i==1
            myveca.insert(pos,A(10));
            break;
        }
    }
    for(int i=0;i<5;++i){
        printf("下标为%d的元素的地址是%p，m_i=%d\n",i,&myveca[i],myveca[i].m_i);
    }
    return 0;
}
