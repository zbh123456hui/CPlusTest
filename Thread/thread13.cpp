#include <iostream>
#include <future>
#include <thread>
#include <vector>

using namespace std;


int mythread(int mypar){
    cout<<mypar<<endl;
    cout<<"mythread() start"<<"threadid="<<this_thread::get_id()<<endl;
    chrono::milliseconds dura(200);
    this_thread::sleep_for(dura);         //休息一定的时长
    cout<<"mythread() end"<<"threadid="<<this_thread::get_id()<<endl;
    return 5;
}



//int main(){
//    cout<<"main"<<"threadid="<<std::this_thread::get_id()<<endl;
//    packaged_task<int(int)> mypt(mythread);
//    //通过packaged_task把各种可调用对象包装起来，方便将来作为线程入口函数来调用
//    thread t1(std::ref(mypt),1);  //线程直接开始执行，第二个参数作为线程入口函数的参数
//    t1.join();  //可以调用这个等待线程执行完毕，不调用的话该程序会崩溃
//    future<int> result=mypt.get_future();  //std::future对象里含有线程入口函数的
//                                    //返回结果，这里用result保存mythread返回的结果
//    cout<<"continue...!"<<endl;
//    cout<<result.get()<<endl;
//    cout<<"main function has finished!"<<endl;
//    return 0;
//}

vector<std::packaged_task<int(int)>> mytasks; //用来代表（包装）一个可调用对象，它所代表的
                                              //这个可调用对象接收一个int参数，返回一个int值。

int main(){
    cout<<"main"<<"threadid="<<std::this_thread::get_id()<<endl;
    packaged_task<int(int)>mypt(mythread);
    //入容器
    mytasks.push_back(std::move(mypt)); //移动语义，入进去后mypt就empty了
    //出容器
    std::packaged_task<int(int)>mypt2;
    auto iter=mytasks.begin();
    mypt2=std::move(*iter);   //用移动语义
    mytasks.erase(iter);      //删除第一个元素，迭代器已经失效，不能再用
    mypt2(123);               //直接调用
    //要取得结果，则还需要借助这个future
    std::future<int> result=mypt2.get_future();
    cout<<result.get()<<endl;
    cout<<"main function has finished!"<<endl;
    return 0;
}