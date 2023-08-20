#include <iostream>

void myfunc(void* ptmp){
    printf("myfunc(void* ptmp)\n");
}
void myfunc(int tmpvalue){
    printf("myfunc(int tmpvalue)\n");
}
int main(){
//    myfunc(NULL);      //编译失败
    myfunc(nullptr);     //void myfunc(void* ptmp)
    return 0;
}