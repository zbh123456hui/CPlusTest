#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex resource_mutex;
std::once_flag g_flag;       //这是一个系统定义的标记
//std::once_flag，这是一个结构，可以理解为一个标记，call_once就是通过该标记来实现只调用一次的功能。

class MyCAS{       //构造一个单例类
private:
    MyCAS(){}      //构造函数是私有的

private:
    static MyCAS* m_instance;

private:
    static void CreateInstance(){
        //如下两行是测试代码
        //std::chrono::milliseconds dura(20000);   //1s=1000ms,所以20000ms=20s
        //std::this_thread::sleep_for(dura);       //休息一定的时长
        m_instance=new MyCAS();
        cout<<"CreateInstance() has finished"<<endl;          //测试用
        static CGarhuishou c1;
    }

public:
    static MyCAS* GetInstance(){
        std::call_once(g_flag,CreateInstance);    //两个线程同时执行到这里时，其中一个线程卡在
        //这行等另外一个线程的该行执行完毕（所以可以把g_flag看成一把锁）
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