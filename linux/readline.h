#ifndef READLINE_H
#define READLINE_H
/**
 *读取1行，bufsize是data数组的大小。最多读bufsize-1个字节。
 *不会把\n存入数组，但是会自动在最后补\0。
 *返回 ：当遇到eof时返回-1。
        当错误时返回-2。
        否则返回的是实际读取的字节数。
**/
int readline(int fd,char* data,int bufsize);
#endif
