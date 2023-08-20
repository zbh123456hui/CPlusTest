#include <iostream>
#include <ctime>
#define MYMEMPOOL 1

using namespace std;

class A{
public:
    static void* operator new(size_t size);
    static void operator delete(void* phead);
    static int m_iCount;          //用于分配计数统计，每new一次+1
    static int m_iMallocCount;    //用于统计malloc次数，每malloc一次+1
private:
    A* next;
    static A* m_FreePosi;         //总是指向一块可以分配出去的内存的首地址
    static int m_sTrunkCount;     //一次分配多少倍该类的内存
};

void* A::operator new(size_t size){
    #ifndef MYMEMPOOL
        A *ppoint=(A*)malloc(size);  //不再用传统方式实现，而是用内存池实现
        return ppoint;
    #endif
    A* tmplink;
    if(m_FreePosi==nullptr){
        //为空，需要申请内存，申请一块很大的内存
        size_t realsize=m_sTrunkCount*size;  //申请m_sTrunkCount这么多倍的内存
        m_FreePosi=reinterpret_cast<A*>(new char[realsize]); //这是传统new，调用底层传统malloc
        tmplink=m_FreePosi;

        //把分配出来的这一大块内存链接起来，供后续使用
        for(;tmplink!=&m_FreePosi[m_sTrunkCount-1];++tmplink){
            tmplink->next=tmplink+1;
        }
        tmplink->next=nullptr;
        ++m_iMallocCount;
    }
    tmplink=m_FreePosi;
    m_FreePosi=m_FreePosi->next;
    ++m_iCount;
    return tmplink;
}
void A::operator delete(void* phead){
    #ifdef MYMEMPOOL
        free(phead);                //不再用传统方法实现，针对内存池有特别的实现
        return;
    #endif
    (static_cast<A*>(phead))->next=m_FreePosi;
    m_FreePosi=static_cast<A*>(phead);
}

//----------------------------------------------------------------------------------------------------
int A::m_iCount=0;
int A::m_iMallocCount=0;
A* A::m_FreePosi=nullptr;
int A::m_sTrunkCount=5;         //一次分配5倍的该类内存作为内存池的大小

int main(){
    //和时间有关的类型：typedef long clock_t
    clock_t start,end;         //包含头文件#include <ctime>
    start=clock();             //程序运行到此刻所花费的时间（单位：毫秒）
    for(int i=0;i<5000000;i++){
        A* pa=new A();
        //printf("%p\n",pa);
    }
    end=clock();
    cout<<"申请分配内存的次数为："<<A::m_iCount<<"实际malloc次数为："<<A::m_iMallocCount<<"用时（毫秒）："<<end-start<<endl;
    return 0;
}