#include"tcpsocket.h"
#include<iostream>
using namespace std;
int main()
{
    tcp_server server;

    auto success=server.start_accept_from("127.0.0.1",23456);
    if(!success) cout<<"can't not listen!"<<endl;
    while(1)
    {
        if(server.pending_count()>0)
        {
            auto client=server.get_pending_socket();
            if(client==0) continue;
            cout<<client.peer_ip()<<endl;
            cout<<client.peer_port()<<endl;
            char buf[200];
            int cnt=client.read(buf,200);
            buf[cnt]=0;
            cout<<buf<<endl;
        }
    }
}

