#ifndef LIU_SOCKET_H
#define LIU_SOCKET_H

#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")  // if you use g++,you should add build option -lws2_32
#pragma comment(lib,"pthread")     // if you use g++,you should add build option -pthread
#include <winsock2.h>
#include <WS2tcpip.h>
#define SOCKET SOCKET
#endif
#include<iostream>
#include <string>
#include <queue>
#include <atomic>
#include <thread>
using namespace std;
class tcp_abstract_socket;
class tcp_server;
class tcp_socket;
class tcp_abstract_socket
{
    public:
    enum socket_state
    {
        none, // if this is not a socket.
        un_init,  
        init,
        connecting,
        connected,
        listening,
    };
    /// @brief return local socket state
    socket_state state();
    /// @brief return local socket ip
    /// @return return local socket ip
    string ip();
    /// @brief return local socket port
    /// @return return local socket port
    int port();

    /// @brief if type is 0 and socket state is none ,return true,else return false
    /// @param type can be 0 or other interger.
    /// @return if type is 0 and socket state is none ,return true,else return false
    bool operator==(int type);
    // @brief see socket library's setsockopt,this method just use this function.
    int set_opt(int __level, int __optname, const char *__optval, socklen_t __optlen);

    protected:
    atomic<socket_state> *_state;
    SOCKET *_socket;
    atomic<int> *cnt;
    tcp_abstract_socket();
    tcp_abstract_socket(socket_state type);
    tcp_abstract_socket(const tcp_abstract_socket& other);
    void operator=(const tcp_abstract_socket& other);
    virtual ~tcp_abstract_socket();
};

class tcp_socket:public tcp_abstract_socket
{
    public:
    tcp_socket(){}
    bool operator==(int type){return tcp_abstract_socket::operator==(type);}



    /// @brief connect to host with ip and port,make sure the socket state is init before using this method.
    /// @return true if successfully connect,else false.
    bool connect_to_host(const string &ip,int port);
    /// @brief disconnect from host
    /// @return true if success else false;
    bool disconnet();
    /// @brief write len byte to peer
    /// @param buf 
    /// @param len 
    /// @return return numbers of actually send bytes,-1 if failed. 
    int write(const char* buf,int len);
    /// @brief read len bytes from peer.
    /// @param buf 
    /// @param len 
    /// @return return numbers of actully read bytes,-1 if failed.
    int read(char* buf,int len);
    /// @brief get the peer ip
    /// @return 
    string peer_ip();
    /// @brief get the peer port
    /// @return 
    int peer_port();
    private:
    tcp_socket(socket_state type):tcp_abstract_socket(type){}
    
    friend tcp_server;
    
};
class tcp_server :public tcp_abstract_socket
{
    public:
    /// @brief listen at ip and port.and then start a thread to accept from the socket,when successfully accept a client,add it to a queue.you can use get_pending socket to get the client.
    /// @return true if success else false;
    bool start_accept_from(const string &ip,int port);
    bool operator==(int type){return tcp_abstract_socket::operator==(type);}
    // @brief return a pending socket,if there are no pending socket ,return a socket which can act like tcp_socket==0;
    tcp_socket get_pending_socket();
    /// @brief return the number of pending clients.
    int pending_count();
    private:
    void accept_func();
    queue<tcp_socket> pending_queue;
    thread t;
};
tcp_abstract_socket::tcp_abstract_socket()
{
    cnt=new atomic<int>(0);
    _socket=new SOCKET;
    _state=new atomic<socket_state>;
    (*cnt)++;
    WSADATA _wsadata;
    _state->store(un_init);
    if (0 != WSAStartup(MAKEWORD(2, 2), &_wsadata)) return;
    *_socket = socket(AF_INET, SOCK_STREAM, 0);
    _state->store(init);
}
tcp_abstract_socket::tcp_abstract_socket(const tcp_abstract_socket &other)
{
    (*other.cnt)++;
    this->cnt=other.cnt;
    this->_state=other._state;
    this->_socket=other._socket;
}
tcp_abstract_socket::tcp_abstract_socket(tcp_abstract_socket::socket_state type)
{
    cnt=new atomic<int>(0);
    _state=new atomic<socket_state>;
    _socket=nullptr;
    (*cnt)++;
    _state->store(none);
}
bool tcp_abstract_socket::operator==(int type)
{
    if(type==0&&_state->load()==none)
    {
        return true;
    }
    else return false;
}
void tcp_abstract_socket::operator=(const tcp_abstract_socket &other)
{
    (*(this->cnt))--;
    if(*cnt==0)
    {
        delete this->cnt;
        delete this->_socket;
        delete this->_state;
    }
    this->cnt=other.cnt;
    this->_state=other._state;
    this->_socket=other._socket;
}

tcp_abstract_socket::~tcp_abstract_socket()
{
    (*cnt)--;
    if(*cnt==0)
    {
        delete this->cnt;
        delete this->_socket;
        delete this->_state;
    }

}

tcp_abstract_socket::socket_state tcp_abstract_socket::state()
{
    return _state->load();
}

string tcp_abstract_socket::ip()
{
    SOCKADDR_IN addr;
    int len=sizeof(addr);
    getsockname(*_socket,(sockaddr*)&addr,&len);
    //cout<<addr.sin_addr.S_un.S_addr<<endl;
    return inet_ntoa(addr.sin_addr);
}

int tcp_abstract_socket::port()
{
    SOCKADDR_IN addr;
    int len=sizeof(addr);
    getsockname(*_socket,(sockaddr*)&addr,&len);
    return ntohs(addr.sin_port);
}
int tcp_abstract_socket::set_opt(int __level, int __optname, const char *__optval, socklen_t __optlen)
{
    return setsockopt(*_socket,__level,__optname,__optval, __optlen);
}

bool tcp_server::start_accept_from(const string &ip, int port)
{
    if(_state->load()!=init) return false;
    SOCKADDR_IN addr;                                  //需要绑定的参数，主要是本地的socket的一些信息。
    auto int_ip=inet_addr(ip.c_str());
    if(int_ip==INADDR_NONE) return false;
    addr.sin_addr.S_un.S_addr = int_ip;     //ip地址，htonl即host本机 to:to  n:net l:unsigned long 大端存储，低字节在高位
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);                       //端口 htons将无符号短整型转化为网络字节序
	if(SOCKET_ERROR==::bind(*_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR))) return false;
    if(SOCKET_ERROR==listen(*_socket,10))
    {
        closesocket(*_socket);
        return false;
    }
    _state->store(listening);
    t=thread(&tcp_server::accept_func,this);
    return true;

}

tcp_socket tcp_server::get_pending_socket()
{
    if(pending_queue.size()>0)
    {
        auto temp=pending_queue.front();
        pending_queue.pop();
        return temp;
    }
    else return tcp_socket(none);
}

int tcp_server::pending_count()
{
    return pending_queue.size();
}

void tcp_server::accept_func()
{
    while(_state->load()==listening)
    {
        SOCKADDR_IN clientsocket;
		int len = sizeof(SOCKADDR);
		SOCKET serConn = accept(*_socket, (SOCKADDR*)&clientsocket, &len);//于客户端建立链接
        tcp_socket temp;
        *temp._socket=serConn;
        temp._state->store(connected);
        pending_queue.push(temp);
    }
}



bool tcp_socket::connect_to_host(const string& ip, int port)
{
    if(_state->load()!=init)
    {
        return false;
    }
    SOCKADDR_IN client_in;
    client_in.sin_addr.S_un.S_addr = inet_addr(ip.c_str());//将网络地址字符串转换成二进制形式
    client_in.sin_family = AF_INET;
    client_in.sin_port = htons(port);
    _state->store(connecting);
    if(0==connect(*_socket, (SOCKADDR*)&client_in, sizeof(SOCKADDR)))
    {
        _state->store(connected);
        return true;
    }
    else
    {
        _state->store(init);
        return false;
        
    }
}

bool tcp_socket::disconnet()
{
    if(_state->load()!=connected)
    {
        return false;
    }
    if(::closesocket(*_socket)==-1)
    {
        return false;
    }
    else
    {
        _state->store(init);
        return true;
    }
}

int tcp_socket::write(const char *buf, int len)
{
    if(_state->load()!=connected)
    {
        return -1;
    }
    int retval=send(*_socket,buf,len,0);
    return retval;
}

int tcp_socket::read(char *buf, int len)
{
    if(_state->load()!=connected)
    {
        return -1;
    }
    int retval=recv(*_socket,buf,len,0);
    return retval;
}

string tcp_socket::peer_ip()
{
    SOCKADDR_IN addr;
    int len=sizeof(addr);
    char _ip[20];
    getpeername(*_socket,(sockaddr*)&addr,&len);
    return inet_ntoa(addr.sin_addr);
}

int tcp_socket::peer_port()
{
    SOCKADDR_IN addr;
    int len=sizeof(addr);
    getpeername(*_socket,(sockaddr*)&addr,&len);
    return ntohs(addr.sin_port);
}
#endif