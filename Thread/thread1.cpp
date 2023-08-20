#include <iostream>
#include <thread>

void myprint(){
    std::cout<<"My thread is started!"<<std::endl;
    std::cout<<"My thread is finished!"<<std::endl;
    return;
}

int main(){
    std::thread mytobj(myprint);    //创建一个线程，也可以称为创建一个子线程
    std::cout<<mytobj.joinable()<<std::endl;  //判断是否可以成功使用join()或detach()  
    mytobj.join();    //加入join后，程序阻塞至子线程完成后运行
    //mytobj.detach();    //加入detach后，程序也不再报异常，能正常运行
    //针对一个线程，join()与detach()只能调用一个
    std::cout<<"Main thread is finished!"<<std::endl;
    return 0;
}