#include <iostream>
#include <ctime>

using namespace std;

//专门的内存池类
class myallocator{              //必须保证使用本类的类sizeof()不少于4字节，否则崩溃报错
public:
    //分配内存接口
    void* allocate(size_t size){
        obj* tmplink;
        if(m_FreePosi==nullptr){
            //为空，需要申请内存，申请一块很大的内存
            size_t realsize=m_sTrunkCount*size;  //申请m_sTrunkCount这么多倍的内存
            m_FreePosi=(obj*)malloc(realsize);
            tmplink=m_FreePosi;

            //把分配出来的这一大块内存彼此链接起来，共后面使用
            for(int i=0;i<m_sTrunkCount-1;++i){
                tmplink->next=(obj*)((char*)tmplink+size);
                tmplink=tmplink->next;
            }//end for
            tmplink->next=nullptr;            
        }//end if
        tmplink=m_FreePosi;
        m_FreePosi=m_FreePosi->next;
        return tmplink;
    }

    //释放内存接口
    void deallocate(void* phead){
        ((obj*)phead)->next=m_FreePosi;
        m_FreePosi=(obj*)phead;
    }
private:
    //写在类内的结构，这样只能在类内使用
    struct obj{
        struct obj* next;       //这个next就是一个嵌入式指针
    };
    int m_sTrunkCount=5;         //一次分配5倍的该类内存作为内存池的大小
    obj* m_FreePosi=nullptr;
} ; 

class A{
public:
    //必须保证sizeof(A)凑够4字节，这里两个int成员8字节了，所以使用类myallocator没有问题
    int m_i;
    int m_j;
public:
    static myallocator myalloc;   //静态成员变量，跟着类A走
    static void* operator new(size_t size){
        return myalloc.allocate(size);
    }
    static void operator delete(void* phead){
        return myalloc.deallocate(phead);
    }
};


myallocator A::myalloc;         //在类A之外定义一下这个静态成员变量


//----------------------------------------------------------------------------------------------------        

int main(){
    A* mypa[100];
    for(int i=0;i<15;++i){
        mypa[i]=new A();
        printf("%p\n",mypa[i]);
    }
    for(int i=0;i<15;++i){
        delete mypa[i];
    }
    return 0;
}