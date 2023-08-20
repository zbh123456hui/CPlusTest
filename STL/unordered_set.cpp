#include <unordered_set>
#include <iostream>

using namespace std;

int main(){
    unordered_set<int>myset;
    cout<<"bucket_count()="<<myset.bucket_count()<<endl;  //篮子数量：1
    for(int i=0;i<8;++i){
        myset.insert(i);
    }
    cout<<"bucket_count()="<<myset.bucket_count()<<endl; //13
    myset.insert(8); //装第9个元素，看篮子数量是否增加
    cout<<"bucket_count()="<<myset.bucket_count()<<endl; //13
    cout<<"max_bucket_count()="<<myset.max_bucket_count()<<endl;  //最大篮子数量：536870911
    printf("所有篮子（本容器）里有的元素数量为%d\n",myset.size());  //9
    //打印每个篮子里的元素个数
    for(int i=0;i<myset.bucket_count();++i){
        printf("第%d个篮子里有的元素数量为%d\n",i,myset.bucket_size(i)); //从0开始
    }
    auto pmyfind=myset.find(5);//对于查找操作，尽可能用容器提供的，效率最高，如没有则考虑用全局的find函数
    if(pmyfind!=myset.end()){
        cout<<"元素5存在于容器中"<<endl;
    }
    return 0;
}