#include <iostream>
#include <thread>

using namespace std;

class A{
public:
    int m_i;
    A(int a):m_i(a){
        cout<<"A::A(int a)'s constructor is worked, this="<<this<<",threadid="<<std::this_thread::get_id()<<endl;
    }
    A(const A& a){
        cout<<"A::A(const A)'s copy constructor is worked, this="<<this<<",threadid="<<std::this_thread::get_id()<<endl;
    }
    ~A(){
        cout<<"~A::A()'s destructor is worked, this="<<this<<",threadid="<<std::this_thread::get_id()<<endl;
    }
    void thread_work(int num){
        cout<<"sub-thread's thread_work is worked, this="<<this<<",threadid="<<std::this_thread::get_id()<<endl;
    }
    void operator()(int num){
        cout<<"sub-thread's () is worked, this="<<this<<",threadid="<<std::this_thread::get_id()<<endl;
    }
};

//void myprint2(const A& pmybuf){
//    cout<<"sub-thread 'myprint2''s parameter pmybuf's address is:"<<&pmybuf<<",threadid="<<std::this_thread::get_id()<<endl;
//}

void myprint2(A& pmybuf){
    cout<<"sub-thread 'myprint2''s parameter pmybuf's address is:"<<&pmybuf<<",threadid="<<std::this_thread::get_id()<<endl;
}

int main(){
    cout<<"Main thread's threadid="<<std::this_thread::get_id()<<endl;
    int mvar=1;
    A myobj(10);
//    A myobj2=myobj;
//    std::thread mytobj(myprint2,mvar);
//    std::thread mytobj(myprint2,A(mvar));
//    std::thread mytobj(myprint2,std::ref(myobj));
//    std::thread mytobj(&A::thread_work,myobj,15);
    std::thread mytobj(&A::thread_work,&myobj,15);
//    thread mytobj(myobj,15);
//    thread mytobj(std::ref(myobj),15);
    mytobj.join();
    cout<<"Main thread is finished!"<<endl;
    return 0;
}