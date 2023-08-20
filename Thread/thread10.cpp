#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>

//(1)例如当inMsgRecvQueue执行完，若没有唤醒outMsgRecvQueue，则outMsg-
//RecvQueue的执行流程会一直卡在wait所在行。
//(2)当wait有第二个参数时，这个参数是一个可调用对象，如函数、lambda表达式等都
//属于可调用对象。后面章节也会专门讲解可调用对象。
//(3)假如outMsgRecvQueue正在处理一个事务，需要一段时间，而不是正卡在wait行
//进行等待，那么此时inMsgRecvQueue中调用的notify_one也许不会产生任何效果。

using namespace std;

class A{
public:
    void inMsgRecvQueue(){
        for(int i=0;i<1000;i++){
            cout<<"inMsgRecvQueue() executed, inserting an element"<<i<<endl;
            std::unique_lock<std::mutex> sbguard1(my_mutex);
            msgRecvQueue.push_back(i);
            my_cond.notify_one();  //尝试把卡（堵塞）在wait()的线程唤醒，但仅唤醒了还不够，这里必须把互斥量解锁，
                                   //另外一个线程的wait()才会继续工作
        }
        return;
    }
    void outMsgRecvQueue(){
        int command=0;
        while(true){
            std::unique_lock<std::mutex> sbguard1(my_mutex);  //临界进去
            //wait()用于等一个东西
            //如果wait()第二个参数的lambda表达式返回的是true，wait就直接返回
            //如果wait()第二个参数的lambda表达式返回的是false，那么wait（）将解锁互斥量并堵
            //塞到这行。那堵到什么时候为止呢？堵到其他某个线程调用notify_one()通知为止
            //如果wait()不用第二个参数，那跟第二个参数为lambda表达式并且返回false效果一样
            //（解锁互斥量并堵塞到这行，堵到其他某个线程调用notify_one()通知为止）
            my_cond.wait(sbguard1,[this]{
                if(!msgRecvQueue.empty()){
                    return true;
                }
                return false;
            });
            //现在互斥量是锁着的，流程走下来意味着msgRecvQueue队列里必然有数据
            command=msgRecvQueue.front();      //返回第一个元素，但不检查元素是否存在
            msgRecvQueue.pop_front();          //移除第一个元素，但不返回
            sbguard1.unlock();   //因为unique_lock的灵活性，可以随时unlock解锁，以免锁住太长时间
            cout<<"OutMsgRecvQueue() executed, extracting an element from the container"<<command<<endl;
        }//end while
    }
private:
    std::list<int>msgRecvQueue;
    std::mutex my_mutex;   //创建互斥量
    std::condition_variable my_cond;    //生成一个条件对象
};

int main(){
    A myobja;
    std::thread myOutnMsgObj(&A::outMsgRecvQueue,&myobja);
    std::thread myInMsgObj(&A::inMsgRecvQueue,&myobja);
    myInMsgObj.join();
    myOutnMsgObj.join();
    cout<<"main()主函数执行结束！"<<endl;
    return 0;
}