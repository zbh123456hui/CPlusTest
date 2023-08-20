#include <iostream>
#include <thread>
#include <vector>
#include <iterator>

using namespace std;

void myprint(int inum){
    cout<<"myprint thread is started,thread number is "<<inum<<endl;

    cout<<"myprint thread is finished,thread number is "<<inum<<endl;
    return;
}

int main(){
    vector<thread> mythreads;
    for(int i=0;i<5;i++){
        mythreads.push_back(thread(myprint,i));  //创建并开始执行线程
    }
    for(auto iter=mythreads.begin();iter!=mythreads.end();++iter){
        iter->join();      //等待5各线程都返回
    }
    cout<<"main function is finished!"<<endl;   //进程退出
    return 0;
}