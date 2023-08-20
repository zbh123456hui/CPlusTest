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
            //my_mutex.lock();      //要操作共享数据，所以先加锁
            //std::lock_guard<std::mutex>sbguard(my_mutex);
            std::unique_lock<std::mutex>sbguard(my_mutex);
            msgRecvQueue.push_back(i);
            //my_mutex.unlock();    //共享数据操作完毕，解锁
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
        std::unique_lock<std::mutex> sbguard(my_mutex);  //sbguard是随意起的变量名
        //my_mutex.lock();
        if(!msgRecvQueue.empty()){
            command=msgRecvQueue.front();
            msgRecvQueue.pop_front();
            //my_mutex.unlock();
            return true;
        }
        //my_mutex.unlock();
        return false;
    }
    
private:
    std::list<int>msgRecvQueue;
    std::mutex my_mutex;   //创建互斥量
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