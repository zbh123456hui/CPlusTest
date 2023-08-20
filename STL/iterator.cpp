#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>


using namespace std;

void _display_category(random_access_iterator_tag mytag){   //随机访问迭代器
    cout<<"random_access_iterator_tag"<<endl;
}
void _display_category(bidirectional_iterator_tag mytag){   //双向迭代器
    cout<<"bidirectional_iterator_tag"<<endl;
}
void _display_category(forward_iterator_tag mytag){        //前向迭代器
    cout<<"forward_iterator_tag"<<endl;
}
void _display_category(output_iterator_tag mytag){         //输出型迭代器
    cout<<"output_iterator_tag"<<endl;
}
void _display_category(input_iterator_tag mytag){          //输入型迭代器
    cout<<"input_iterator_tag"<<endl;
}
template <typename T>
void display_category(T iter){  //编译器能推导出类型来
    cout<<"-----------------begin-----------------"<<endl;
    typename iterator_traits<T>::iterator_category cagy;  //这个是过滤器（萃取机），用来获取T迭代器类型的种类
    _display_category(cagy);  //这里编译器能够帮助我们找到最适当的重载函数
    cout<<"typeid(iter).name()="<<typeid(iter).name()<<endl;  //打印名称类型
    cout<<"------------------end------------------"<<endl;
} 

int main(){
    display_category(array<int,100>::iterator());   //加()用于产生临时对象
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(map<int,int>::iterator());
    display_category(set<int>::iterator());
}
