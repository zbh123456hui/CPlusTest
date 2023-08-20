#include <iostream>
#include <future>
#include <thread>

using namespace std;

//std::promise是一个类模板，其作用为能够在某个线程中为其赋值，然后可以在其他
//的线程中，把这个值取出来使用。


void mythread(std::promise<int>&tmpp, int calc){
    cout<<"mythread() start"<<"threadid="<<this_thread::get_id()<<endl;
    //做了一系列的复杂操作
    calc++;
    calc*=10;
    //做其他工作，花费2s时间
    chrono::milliseconds dura(2000);
    this_thread::sleep_for(dura);

    //终于计算出了结果
    int result=calc;               //保存结果
    tmpp.set_value(result);        //结果保存到了tmpp这个对象中
    cout<<"mythread() end"<<"threadid="<<this_thread::get_id()<<endl;
}



int main(){
    cout<<"main"<<"threadid="<<std::this_thread::get_id()<<endl;
    std::promise<int> myprom;  //声明std::promise对象myprom，保存的值类型为int
    //创建一个线程t1，将函数mythread及对象myprom作为参数放进去
    thread t1(mythread,std::ref(myprom),180);
    t1.join();   //等线程执行完毕，这个必须有，否则会报异常，join放在.get后面也可以
    //获取结果值
    future<int> ful=myprom.get_future();  //promise和future绑定用于获取线程返回值
    auto result=ful.get();   //获取值，但是这种get因为一些内部特殊操作，不能get多次，只能get一次
    cout<<"continue...!"<<endl;
    cout<<"result="<<result<<endl;
    cout<<"main function has finished!"<<endl;
    return 0;
}