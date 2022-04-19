#ifndef DIRREADER_H
#define DIRREADER_H
#include<map>
#include<string>
#include<set>
#include<vector>
using namespace std;
class DirReader
{
    public:
    vector<string> withoutSubDirFileList;
    
    vector<string> withSubDirFileList;
    vector<string> subDirList;
    vector<string> subSubDirList;
    
    string dir;
    bool isSuccess;
    set<string> ignoreDirList;

    DirReader();

    bool read(string dir);
    void addIgnoreDir(string dir);//忽略《待遍历目录/dir》 下的所有文件以及文件夹。
    /*    
举例：有如下情况（home目录下有c++和python两个子目录，当前在c++目录）
我要遍历当前目录(home/c++)的上级目录(home)，但忽略python目录下的lab3文件夹
那么应该
addIgnoreDir("python/lab3");   //read时将会忽略../python/lab3,".."的来源是下面的read函数。
read("..");
这种情况下datapy.txt不会被忽略
| home
* | c++   <- 当前目录
* * data.txt
* * | lab1
* * * main.cpp
* * | lab2
* * * main.cpp
* * | lab3
* * * main.cpp
* * | lab4
* * * main.cpp
* | python
* * datapy.txt   <- 示例中提到的datapy.txt不会被忽略
* * | lab1
* * * main.py
* * | lab2
* * * main.py
* * | lab3
* * * main.py    <- 被忽略
* * * | tool        <- 被忽略
* * * * tool.py   <- 被忽略
* * | lab4
* * * main.py
*/
    void deleteIgnoreDir(string dir);
    
    private:
    void readsub(string subdir);
    
};
#endif