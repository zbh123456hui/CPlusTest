#include <iostream>
#include <memory>

using namespace std;

int main(){
    shared_ptr<int>pi(new int(100));  //pi指向一个值为100的int型数据
//  shared_ptr<int>pi=new int(100);   //智能指针是explicit，不可以隐式类型转换
    auto p5=make_shared<string>(5,'a') ;
    auto p6(p5);
    int icount=p6.use_count();
    printf("%d\n",icount);
    p6.reset();        //释放p6指向的对象，将pi置空
    if(p5.unique()){
        cout<<"p5 is unique"<<endl;
    }else{
        cout<<"p5 is not unique"<<endl;
    }
    return 0;
}

shared_ptr<int> makes(int values){
    return shared_ptr<int>(new int(values));//显式用int*创建shared_ptr<int>
}