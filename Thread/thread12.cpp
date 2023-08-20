#include <iostream>
#include <future>
#include <thread>

using namespace std;

class A{
public:
    int mythread(){
        cout<<"mythread() start"<<" threadid= "<<this_thread::get_id()<<endl;
        chrono::milliseconds dura(200);
        this_thread::sleep_for(dura);
       cout<<"mythread() end"<<" threadid= "<<this_thread::get_id()<<endl;
        return 5;
    }
    //int mythread(int mypar){
    //    cout<<mypar<<endl;
    //    cout<<"mythread() start"<<"threadid="<<this_thread::get_id()<<endl;
    //    chrono::milliseconds dura(200);
    //    this_thread::sleep_for(dura);
    //    cout<<"mythread() end"<<"threadid="<<this_thread::get_id()<<endl;
    //    return 5;
    //}
};


int main(){
    A a;
    //int tmppar=12;
    cout<<"main"<<" threadid="<<std::this_thread::get_id()<<endl;
    //std::future提供了一种访问异步操作结果的机制，即结果可能不能马上拿到，但将来线程执行完了，就可以拿到
    std::future<int> result=std::async(&A::mythread,&a);  //流程并不会卡在这里，注意如果线程
                                                          //入口函数需要参数，可以把参数放在
                                                          //async的第二个参数的位置
    //future<int> result=async(&A::mythread,&a,tmppar);
    //auto result=std::async(std::launch::deferred,&A::mythread,&a);  //async没有创建新线程，而是在主线程
                                                                             //调用了mythread线程入口函数
    //auto result=std::async(std::launch::async,&A::mythread,&a);     //系统必须创建新线程来执行
    //auto result=std::async(std::launch::async|std::launch::deferred,&A::mythread,&a);  //系统自行决定何操作，与不加的情况相同

    cout<<"continue...!"<<endl;
    cout<<result.get()<<endl;    //卡在这里等待线程执行完，但是这种get因为一些内部特殊操作，
                                 //不能get多次，只能get一次，否则执行会报异常
    //result.wait();               //卡在这里等待线程执行完，但无需返回值
    cout<<"main function has finished!"<<endl;
    return 0;
}