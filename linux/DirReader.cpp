#include<string>
#include<vector>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <set>
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
    void addIgnoreDir(string dir);
    void deleteIgnoreDir(string dir);
    
    private:
    void readsub(string subdir);
    
};
void DirReader::addIgnoreDir(string dir)
{
    if(dir.back()=='/')
    {
        dir.erase(dir.end()-1);
    }
    ignoreDirList.insert(dir);
}
void DirReader::deleteIgnoreDir(string dir)
{
    if(dir.back()=='/')
    {
        dir.erase(dir.end()-1);
    }
    ignoreDirList.erase(dir);
}
bool DirReader::read(string dir)
{
    this->dir=dir;
    if(this->dir.back()=='/')
    {
        this->dir.erase(this->dir.end()-1);
    }
    withoutSubDirFileList.clear();
    withSubDirFileList.clear();
    subDirList.clear();
    subSubDirList.clear();
    isSuccess=false;
    DIR *cdir;
	struct dirent *ptr;
	if(!(cdir = opendir(this->dir.c_str())))
	{
		return false;
	}
	while((ptr = readdir(cdir)) != 0)
	{
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
		{
			continue;
		}
        if(ptr->d_type==DT_REG)//normal file
        {
            withoutSubDirFileList.push_back(ptr->d_name);
            withSubDirFileList.push_back(ptr->d_name);
        }
        else if(ptr->d_type==DT_DIR)
        {
            subDirList.push_back(ptr->d_name);
            subSubDirList.push_back(ptr->d_name);
            if(ignoreDirList.find(string(ptr->d_name))==ignoreDirList.end())
            {
                readsub(this->dir+"/"+ptr->d_name);
            }
            
        }
	}
	closedir(cdir);
    isSuccess=true;
	return true;
}
void DirReader::readsub(string subdir)
{
    DIR *cdir;
	struct dirent *ptr;
	cdir = opendir(subdir.c_str());
	while((ptr = readdir(cdir)) != 0)
	{
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
		{
			continue;
		}
        if(ptr->d_type==DT_REG)//normal file
        {
            withSubDirFileList.push_back(string(subdir.begin()+subdir.find("/")+1,subdir.end())+"/"+ptr->d_name);
        }
        else if(ptr->d_type==DT_DIR)
        {
            string need_push=string(subdir.begin()+subdir.find("/")+1,subdir.end())+"/"+ptr->d_name;
            subSubDirList.push_back(need_push);
            if(ignoreDirList.find(need_push)==ignoreDirList.end())
            {
                readsub(subdir+"/"+ptr->d_name);
            }
        }
	}
	closedir(cdir);
    isSuccess=true;
}
DirReader::DirReader()
{
    isSuccess=false;
}
/*  for demo
int main()
{
    DirReader dirReader;
    dirReader.addIgnoreDir("imp");
    dirReader.addIgnoreDir("inc");
    dirReader.addIgnoreDir("tester-linux-x64");
    dirReader.read("..");
    cout<<"------------------withoutSubDirFileList:"<<endl;
    for(int i=0;i<dirReader.withoutSubDirFileList.size();i++)
    {
        cout<<dirReader.withoutSubDirFileList[i]<<endl;
    }
    cout<<"-----------------withSubDirFileList:"<<endl;
    for(int i=0;i<dirReader.withSubDirFileList.size();i++)
    {
        cout<<dirReader.withSubDirFileList[i]<<endl;
    }
    cout<<"-----------------subDirList:"<<endl;
    for(int i=0;i<dirReader.subDirList.size();i++)
    {
        cout<<dirReader.subDirList[i]<<endl;
    }
    cout<<"-----------------subSubDirList:"<<endl;
    for(int i=0;i<dirReader.subSubDirList.size();i++)
    {
        cout<<dirReader.subSubDirList[i]<<endl;
    }

}
*/