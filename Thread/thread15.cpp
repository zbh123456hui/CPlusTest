#include <iostream>
#include <future>
#include <thread>

using namespace std;


int mythread(int mypar){
    cout<<"mythread() start"<<" threadid="<<this_thread::get_id()<<endl;
    chrono::milliseconds dura(200);   //1s=1000ms,所以200ms=0.2s
    this_thread::sleep_for(dura);     //休息一定的时长
    return 5;
}
void mythread2(std::shared_future<int>& tmpf){    //注意参数
    cout<<"mythread2() start"<<" threadid="<<this_thread::get_id()<<endl;
    auto result=tmpf.get();           //获取值，只能get一次否则会报异常
    cout<<"mythread2 result="<<result<<endl;
    return;
}

int main(){
    cout<<"main"<<" threadid="<<std::this_thread::get_id()<<endl;
    packaged_task<int(int)> mypt(mythread);  //把函数mythread通过packaged_task包装起来
    thread t1(std::ref(mypt),1); //线程直接开始执行，第二个参数作为线程入口函数的参数
    t1.join();   //调用这个等待线程执行完毕，不调用这个不行，程序会崩溃
    future<int> result=mypt.get_future();
    //valid，判断future对象里面的值是否有效
    bool ifcanget=result.valid(); //没有被get过表示能通过get获取，则这里返回true
    //auto mythreadresult=result.get(); //获取值，只能get一次否则会报异常
    //ifcanget=result.valid(); //future对象get过了，里面的值就没了，这时就返回false
    std::shared_future<int> result_s(std::move(result));  //std::move(result)也可以替换成
                                        //result.share()，在没针对result调用get时，把result
                                        //的内容弄到shared_future中来，此时future中空了
    ifcanget=result.valid();  //因为result中空了，所以ifcanget为false了，这时不能再用result内容
    ifcanget=result_s.valid();  //因为result_s里有内容了，所以ifcanget为true了
    auto mythreadresult=result_s.get();
    thread t2(mythread2,std::ref(result_s));
    t2.join();  //等线程执行完毕
    cout<<"main function has finished!"<<endl;
    return 0;
}