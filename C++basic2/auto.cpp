#include <iostream>

int main(){
    int v[]={12,13,14,16,18};
    for(auto x:v){
    //数组v中每个元素依次放入x并打印x值，相当于把v的每个元素值复制到x中，然后打印                     
        std::cout<<x<<std::endl;
    }
    for(auto& x:v){
    //使用引用的方式，避免数据的复制动作
        std::cout<<x<<std::endl;
    }
    return 0;
}