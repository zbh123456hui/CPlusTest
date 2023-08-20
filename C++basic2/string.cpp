#include <iostream>
#include <string.h>

using namespace std;

int main(){
    string s1="abc";
    const char* p=s1.c_str();     //返回一个字符串s中的内容指针
    char str[100];
    strcpy_s(str,sizeof(str),p);
    cout<<str<<endl;
    return 0;
}