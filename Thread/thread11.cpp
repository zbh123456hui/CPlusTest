#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>

using namespace std;

class A{
public:
    void inMsgRecvQueue(){
        for(int i=0;i<1000;i++){
            cout<<"inMsgRecvQueue() executed, inserting an element"<<i<<endl;
            std::unique_lock<std::mutex> sbguard1(my_mutex);
            msgRecvQueue.push_back(i);
            //my_cond.notify_one();
            my_cond.notify_all();  //尝试把卡（堵塞）在wait()的线程唤醒，但仅唤醒了还不够，这里必须把互斥量解锁，
                                   //另外一个线程的wait()才会继续工作
        }
        return;
    }
    void outMsgRecvQueue(){
        int command=0;
        while(true){
            std::unique_lock<std::mutex> sbguard1(my_mutex);  //临界进去
            my_cond.wait(sbguard1,[this]{
                if(!msgRecvQueue.empty()){
                    return true;
                }
                return false;
                });
            command=msgRecvQueue.front();
            msgRecvQueue.pop_front();
            sbguard1.unlock();
            cout<<"OutMsgRecvQueue() executed, extracting an element from the container"<<command<<" threadid= "<<std::this_thread::get_id<<endl;
        }//end while
        cout<<"end"<<endl;
    }
private:
    std::list<int>msgRecvQueue;
    std::mutex my_mutex;   //创建互斥量
    std::condition_variable my_cond;    //生成一个条件对象
};

int main(){
    A myobja;
    std::thread myOutnMsgObj(&A::outMsgRecvQueue,&myobja);   //第二个参数是引用，才能保证
                                                             //线程里用的是同一个对象
    std::thread myOutnMsgObj2(&A::outMsgRecvQueue,&myobja);  
    std::thread myInMsgObj(&A::inMsgRecvQueue,&myobja);
    myInMsgObj.join();
    myOutnMsgObj2.join();
    myOutnMsgObj.join();
    cout<<"main() function is finished!"<<endl;
    return 0;
}