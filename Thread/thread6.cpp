#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

class A{
public:
    //把收到的消息入到队列的线程
    void inMsgRecvQueue(){
        for(int i=0;i<1000;i++){
            cout<<"inMsgRecvQueue() executed, inserting an element"<<i<<endl;
            msgRecvQueue.push_back(i); //假设这个数字就是收到的命令，则将其直接放到消息队列里
        }
    }

    //把数据从消息队列中读取的线程
    void outMsgRecvQueue(){
        for(int i=0;i<1000;i++){
            if(!msgRecvQueue.empty()){
                int command=msgRecvQueue.front(); //返回第一个元素但不检查元素存在与否
                msgRecvQueue.pop_front();    //移除第一个元素但不返回
//--------------------------这里可以考虑处理数据----------------------//
            }else{
                cout<<"OutMsgRecvQueue() executed, but currently there is an empty element in the receiving message queue"<<i<<endl;
            }
        }
        cout<<"end"<<endl;
    }

private:
    std::list<int> msgRecvQueue; //容器（收消息队列），专门用于发送命令。
};

int main(){
    A myobja;
    std::thread myOutnMsgObj(&A::outMsgRecvQueue,&myobja);  //第二个参数必须是引用（或std::ref），保证线程里用的是同一个对象。
    std::thread myInMsgObj(&A::inMsgRecvQueue,&myobja);
    myInMsgObj.join();
    myOutnMsgObj.join();
    cout<<"main function is finished!"<<endl;
}