#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex resource_mutex;

class MyCAS{       //构造一个单例类
private:
    MyCAS(){}      //构造函数是私有的

private:
    static MyCAS* m_instance;

public:
    static MyCAS* GetInstance(){
        if(m_instance==NULL){
            std::unique_lock<std::mutex> mymutex(resource_mutex); //自动加锁
            if(m_instance==NULL){
                m_instance=new MyCAS();
                static CGarhuishou c1;    //生命周期一直到程序退出
            }
        }
        return m_instance;
    }
    class CGarhuishou{    //类中套类，用于释放对象
    public:
        ~CGarhuishou(){
            if(MyCAS::m_instance){
                delete MyCAS::m_instance;
                MyCAS::m_instance=NULL;
            }
        }
    };
    void func(){         //普通成员函数，用于测试调用
        cout<<"test"<<endl;
    }
};
MyCAS* MyCAS::m_instance=NULL;    //类静态成员变量定义并初始化

void mythread(){
    cout<<"My thread has started."<<endl;
    MyCAS* p_a=MyCAS::GetInstance();    //会出问题
    cout<<"My thread is complete."<<endl;
    return;
}

int main(){
    //MyCAS* p_a=MyCAS::GetInstance();    //创建单例类MyCAS类的对象
    //p_a->func();                        //一条测试语句，用于打印结果
    //MyCAS::GetInstance()->func();       //这种写法的测试语句也可以打印结果
    std::thread mytobj1(mythread);
    std::thread mytobj2(mythread);
    mytobj1.join();
    mytobj2.join();
    return 0;
}