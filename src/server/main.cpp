#include"chatserver.hpp"
#include"chatservice.hpp"
#include<iostream>
#include<signal.h>
using namespace std;

//处理器ctrl + c结束后，重置user 的状态信息，把登录变成未登录
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc,char **argv)
{
    if(argc<3)
    {
        cerr<<"参数过少!example:./ChatServer 127.0.0.1 6000"<<endl;
    }

    //解析通过命令行参数传递的ip和port
    char *ip=argv[1];
    uint16_t port=atoi(argv[2]);


    signal(SIGINT,resetHandler);

    EventLoop loop;
    InetAddress addr(ip,port);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();
    loop.loop();
    return 0;
}