#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
int readline(int fd,char* data,int bufsize)
{
	int i=0;
	int status;
	char buf;
	while(1)
	{
		if(i<=bufsize-2)
		{
			status=read(fd,&buf,1);
			if(status==0)
			{
				return -1;
			}
			else if(status==-1)
			{
				return -2;
			}
			else
			{
				if(buf=='\r')
				{
					continue;
				}
				else if(buf=='\n')
				{
					break;
				}
				else
				{
					data[i++]=buf;
				}
			}
		}
		else
		{
			break;
		}
		
	}
	data[i]=0;
	return i;
}
