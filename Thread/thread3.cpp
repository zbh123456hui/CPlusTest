#include <iostream>
#include <thread>

using namespace std;
//用lambda表达式来创建线程

int main(){
    auto mylamthread=[]{
        cout<<"My thread is started!"<<endl;
        cout<<"My thread is finished!"<<endl; 
    };
    thread mytobj3(mylamthread);
    mytobj3.join();
    cout<<"Main thread is finished!"<<endl;
    return 0;
}