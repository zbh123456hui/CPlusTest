//static_cast：静态转换，编译时类型检查。
//dynamic_cast：主要用来进行父类型转成子类型，运行时类型识别和检查。
//const_cast：去除指针或者引用的const属性，经常使用意味着设计缺陷。
//reinterpret_cast：特殊且危险的类型转换，编译时进行类型转换的检查，用于处理无关类型的转换。

//double f=100.34f;
//int i=(int)f;                 //C风格的
//int i2=static_cast<int>(f);   //C++风格的

//class A{};                      //父类
//class B:public A{};             //子类
//int main(){
//    B b;
//    A a=static_cast<A>(b);      //可把子类转换为父类，不可以把父类转换为子类
//    return 0;
//}