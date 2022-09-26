#ifndef JS_H
#define JS_H
#include<chrono>
#include<iostream>
#include<sstream>
#include<string> 
#include<fstream>
using namespace std;
class jser
{
    public:

    chrono::high_resolution_clock::time_point begin_t;
    chrono::high_resolution_clock::time_point end_t;
    void begin()
    {
        begin_t=chrono::high_resolution_clock::now();
    }
    double end()
    {
        end_t=chrono::high_resolution_clock::now();
        chrono::duration<double> time_span=chrono::duration_cast<chrono::duration<double>>(end_t-begin_t);
        return time_span.count();
    }
} timer;

#endif // JS_H
/**
int main()
{
    timer.begin();
    int a;
    for(int i=0;i<100000;i++)
    {
        a++;
    }
    cout<<timer.end();
}
**/