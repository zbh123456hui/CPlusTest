#include <iostream>
#include <thread>

using namespace std;
//用class类来创建线程
class TA{
public:
    int& m_i;
    TA(int& i):m_i(i){};
    void operator()(){
        cout<<"mi1's value is "<<m_i<<endl;
        cout<<"mi2's value is "<<m_i<<endl;
        cout<<"mi3's value is "<<m_i<<endl;
        cout<<"mi4's value is "<<m_i<<endl;
        cout<<"mi5's value is "<<m_i<<endl;
        cout<<"mi6's value is "<<m_i<<endl;
    }
};

int main(){
    int myi=6;
    TA ta(myi);
    thread mytobj2(ta);
    mytobj2.join();
    cout<<"Main thread is finished!"<<endl;
    return 0;
}