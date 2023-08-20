#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main(){
    vector<int> iv={100,200,300};
    for(vector<int>::iterator iter=iv.begin();iter!=iv.end();iter++){
//        *iter=4;     //可以变更
        cout<<*iter<<endl;
    }
    for(vector<int>::reverse_iterator riter=iv.rbegin();riter!=iv.rend();riter++){
        cout<<*riter<<endl;
    }
        for(vector<int>::const_iterator iter=iv.begin();iter!=iv.end();iter++){
//        *iter=4;     //不可以变更
        cout<<*iter<<endl;
    }
    return 0;
}