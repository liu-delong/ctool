
#include<functional>
#include<random>
#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;
template<class T>
int _cmp(T a,T b)
{
    if(a<b) return -1;
    else if(a==b) return 0;
    else return 1;
}
/**
 * @brief 查找给定值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchEqual(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>)
{
    while(begin<=end)
    {
        int mid=(end-begin)/2+begin;
        int result=cmp(data[mid],value);
        if(result==0) return mid;
        else if(result<0) begin=mid+1;
        else end=mid-1;
    }
    return -1;
}
/**
 * @brief 查找不大于给定值的最大值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchNotGreater(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>)
{
    while(begin<end)
    {
        int mid=(end-begin+1)/2+begin;
        int result=cmp(data[mid],value);
        if(result<=0) begin=mid;
        else end=mid-1;
    }
    if(cmp(data[begin],value)>0) return -1;
    else return begin;
    
}
/**
 * @brief 查找不小于给定值的最小值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchNotSmaller(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>)
{
    while(begin<end)
    {
        int mid=(end-begin)/2+begin;
        int result=cmp(data[mid],value);
        if(result>=0) end=mid;
        else begin=mid+1;
    }
    if(cmp(data[begin],value)<0) return -1;
    else return begin;
}
/**
 * @brief 查找小于给定值的最大值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchSmaller(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>)
{
    while(begin<end)
    {
        int mid=(end-begin+1)/2+begin;
        int result=cmp(data[mid],value);
        if(result>=0) end=mid-1;
        else begin=mid;
    }
    if(cmp(data[begin],value)>=0) return -1;
    else return begin;
}
/**
 * @brief 查找大于给定值的最小值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchGreater(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>)
{
    while(begin<end)
    {
        int mid=(end-begin)/2+begin;
        int result=cmp(data[mid],value);
        if(result<=0) begin=mid+1;
        else end=mid;
    }
    if(cmp(data[begin],value)<=0) return -1;
    else return begin;
}
/*
int main()
{
    int num[14]={0,1,1,3,4,4,5,6,6,7,10,10,10,12};
    uniform_int_distribution<int> u(0,20);
    default_random_engine e;
    e.seed(time(0));
    for(int i=0;i<14;i++)  printf("%4d",i);
    cout<<endl;
    for(int i=0;i<14;i++) printf("%4d",num[i]);
    cout<<endl;
    for(int i=0;i<20;i++)
    {
        int equal_check=u(e);
        int index=BsearchEqual(num,0,13,equal_check);
        cout<<"equal:"<<equal_check<<" "<<index<<endl;
    }

    for(int i=0;i<14;i++)  printf("%4d",i);
    cout<<endl;
    for(int i=0;i<14;i++) printf("%4d",num[i]);
    cout<<endl;
    for(int i=0;i<20;i++)
    {
        int value=u(e);
        cout<<"notGreater:"<<value<<" "<<BsearchNotGreater(num,0,13,value)<<endl;
    }

    for(int i=0;i<14;i++)  printf("%4d",i);
    cout<<endl;
    for(int i=0;i<14;i++) printf("%4d",num[i]);
    cout<<endl;
    for(int i=0;i<20;i++)
    {
        int value=u(e);
        cout<<"notSmaller:"<<value<<" "<<BsearchNotSmaller(num,0,13,value)<<endl;
    }

    for(int i=0;i<14;i++)  printf("%4d",i);
    cout<<endl;
    for(int i=0;i<14;i++) printf("%4d",num[i]);
    cout<<endl;
    for(int i=0;i<20;i++)
    {
        int value=u(e);
        cout<<"Greater:"<<value<<" "<<BsearchGreater(num,0,13,value)<<endl;
    }
    
    for(int i=0;i<14;i++)  printf("%4d",i);
    cout<<endl;
    for(int i=0;i<14;i++) printf("%4d",num[i]);
    cout<<endl;
    for(int i=0;i<20;i++)
    {
        int value=u(e);
        cout<<"smaller:"<<value<<" "<<BsearchSmaller(num,0,13,value)<<endl;
    }
    exit(0);
}
*/