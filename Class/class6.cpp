#include <iostream>

using namespace std;

#pragma pack(1)       //1字节对齐方式
class MYACLS{
public:
    char m_c;
    int m_i;
    static int m_si;
    int m_j;
    static int m_sj;
    int m_k;
    static int m_sk;
public:
    virtual void printMemPoint(){
        cout<<"打印成员变量偏移值------------------"<<endl;
        printf("MYACLS::m_c=%d\n",&MYACLS::m_c);
        printf("MYACLS::m_i=%d\n",&MYACLS::m_i);
        printf("MYACLS::m_j=%d\n",&MYACLS::m_j);
        printf("MYACLS::m_k=%d\n",&MYACLS::m_k);
        cout<<"------------------------------"<<endl;
    }
};
#pragma pack()       //取消指定的1字节对齐方式，恢复默认对齐

int main(){
    MYACLS myobj;
    cout<<sizeof(myobj)<<endl;   //12
    myobj.m_i=myobj.m_j=myobj.m_k=0;
    printf("myobj.m_c=%p\n",&myobj.m_c);
    printf("myobj.m_i=%p\n",&myobj.m_i);
    printf("myobj.m_j=%p\n",&myobj.m_j);
    printf("myobj.m_k=%p\n",&myobj.m_k);

    MYACLS* pmyobj=new MYACLS();
    printf("myobj->m_c=%p\n",&pmyobj->m_c);
    printf("myobj->m_i=%p\n",&pmyobj->m_i);
    printf("myobj->m_j=%p\n",&pmyobj->m_j);
    printf("myobj->m_k=%p\n",&pmyobj->m_k);
    pmyobj->printMemPoint();
}