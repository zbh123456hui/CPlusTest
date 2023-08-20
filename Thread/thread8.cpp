#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

class A{
public:
    void inMsgRecvQueue(){
        for(int i=0;i<1000;i++){
            cout<<"inMsgRecvQueue() executed, inserting an element"<<i<<endl;
            std::lock(my_mutex2,my_mutex1);     //相当于每个互斥量都调用了lock，顺序无所谓；要么两个mutex都锁住，要么都没锁住
            std::lock_guard<std::mutex> sbguard1(my_mutex1,std::adopt_lock);  //通知系统中的互斥量已经被lock过，不需要
            std::lock_guard<std::mutex> sbguard2(my_mutex2,std::adopt_lock);  //std::lock_guard<std::mutex>再次lock
            msgRecvQueue.push_back(i);
            //my_mutex2.unlock();   
            //my_mutex1.unlock(); 
        }
    }
    void outMsgRecvQueue(){
        int command=0;
        for(int i=0;i<1000;i++){
            bool result=outMsgLULProc(command);
            if(result==true){
                cout<<"OutMsgRecvQueue() executed, extracting an element from the container"<<command<<endl;
            }else{
                cout<<"OutMsgRecvQueue() executed, but currently there is an empty element in the receiving message queue"<<i<<endl;
            }
        }
        cout<<"end"<<endl;
    }
    bool outMsgLULProc(int& command){
        std::lock(my_mutex2,my_mutex1);
        std::lock_guard<std::mutex> sbguard1(my_mutex1,std::adopt_lock);
        std::lock_guard<std::mutex> sbguard2(my_mutex2,std::adopt_lock);
        //my_mutex.lock();
        if(!msgRecvQueue.empty()){
            command=msgRecvQueue.front();
            msgRecvQueue.pop_front();
            //my_mutex1.unlock();
            //my_mutex2.unlock();
            return true;
        }
        //my_mutex1.unlock();      //先unlock谁后unlock谁并没关系
        //my_mutex2.unlock();
        return false;
    }
    
private:
    std::list<int>msgRecvQueue;
    std::mutex my_mutex1,my_mutex2;   //创建互斥量
};

int main(){
    A myobja;
    std::thread myOutnMsgObj(&A::outMsgRecvQueue,&myobja);
    std::thread myInMsgObj(&A::inMsgRecvQueue,&myobja);
    myInMsgObj.join();
    myOutnMsgObj.join();
    cout<<"main() function is finished!"<<endl;
    return 0;
}