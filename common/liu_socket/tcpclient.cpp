#include"tcpsocket.h"
using namespace std;
int main()
{
    tcp_socket client;
    cout<<client.connect_to_host("127.0.0.1",23456)<<endl;
    cout<<client.write("hello",5)<<endl;
    cout<<client.disconnet()<<endl;
    cout<<client.connect_to_host("127.0.0.1",23456)<<endl;
    cout<<client.write("hello",5)<<endl;
}