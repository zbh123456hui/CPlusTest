#include <stdio.h>
#include <iostream>

//constexpr用来修饰常量表达式的。所谓常量表达式，指的就是由多个（≥1）常量（值不会改变）组成并且在编译过程中就得到计算结果的表达式。
constexpr int fun(int a){
    a=16;
    int b=5;
    //int c;             编译时会引发错误，必须在定义的时候初始化   
    //printf("good");    编译不过，是constexpr关键字的问题 
    return a*b;
}
int main(){
    constexpr int var=11*fun(12);
    std::cout<<var<<std::endl;
}