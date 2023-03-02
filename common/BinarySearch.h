#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include<functional>
using namespace std;
/**
 * @brief 如果a<b,返回-1，如果a==b,返回0，否则返回1
*/
template<class T>
int _cmp(T a,T b);

/**
 * @brief 查找给定值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchEqual(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>);

/**
 * @brief 查找不大于给定值的最大值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchNotGreater(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>);

/**
 * @brief 查找不小于给定值的最小值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchNotSmaller(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>);

/**
 * @brief 查找小于给定值的最大值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchSmaller(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>);

/**
 * @brief 查找大于给定值的最小值的引索
 * @param begin 包括begin
 * @param end 包括end
 * @param cmp 默认是用<,>,==进行比较。要求模板实例要重载这3个运算符
*/
template<class T>
int BsearchGreater(T data[],int begin,int end,T value,function<int(T,T)> cmp=_cmp<T>);



#endif