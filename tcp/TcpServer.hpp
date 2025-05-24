#include "Log.hpp"
#include "ThreadPool.hpp"
#include"Task.hpp"
#include"Demon.hpp"
//网络四大库
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>
#include<string>

static constexpr const char* defaultip = "0.0.0.0";
static const size_t defaultport = 20001;

enum
{
    UsageError = 1,
    SocketError,
    BindError,
    ListenError,
};


class TcpServer;
class ThreadData
{
public:
    ThreadData(int fd, const std::string &ip, const uint16_t &p, TcpServer *t): sockfd(fd), clientip(ip), clientport(p), tsvr(t)
    {}
public:
    int sockfd;
    std::string clientip;
    uint16_t clientport;
    TcpServer *tsvr;
};

class TcpServer
{
  public:
    TcpServer(uint16_t port=defaultport,std::string ip=defaultip) 
    : listensock_(0), 
    ip_(ip), 
    port_(port) 
    {}
    void InitServer()
    {
        listensock_=socket(AF_INET,SOCK_STREAM,0);
        if(listensock_<0)
        {
            lg(Fatal, "create socket, errno: %d, errstring: %s", errno, strerror(errno));
            exit(SocketError);
        }
        lg(Info, "create socket success, listensock_: %d", listensock_);

        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        inet_pton(AF_INET, ip_.c_str(),&local.sin_addr.s_addr);
        local.sin_port=htons(port_);
        local.sin_family=AF_INET;
        if (bind(listensock_, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            lg(Fatal, "bind error, errno: %d, errstring: %s", errno, strerror(errno));
            exit(BindError);
        }
        lg(Info, "bind socket success, listensock_: %d", listensock_);

        if (listen(listensock_, 128) < 0)
        {
            lg(Fatal, "listen error, errno: %d, errstring: %s", errno, strerror(errno));
            exit(ListenError);
        }
        lg(Info, "listen socket success, listensock_: %d", listensock_);
    }
    void Start()
    {
        lg.Enable(Classfile);
        Demon();
        ThreadPool<Task>::GetInstance()->Start();
        for (;;)
        {
            // 1. 获取新连接
            sockaddr_in client;
            socklen_t len = sizeof(client);
            int sockfd = accept(listensock_, (sockaddr *)&client, &len);
            if (sockfd < 0)
            {
                lg(Error, "sockfderror");
                exit(-1);
            }

            //打印日志
            uint16_t clientport = ntohs(client.sin_port);
            char clientip[32];
            inet_ntop(AF_INET, &(client.sin_addr), clientip, sizeof(clientip));
            lg(Info, "get a new link..., sockfd: %d, client ip: %s, client port: %d", sockfd, clientip, clientport);
            
            //正式通信
            
            //Service(sockfd, clientip, clientport);//单人
            //close(sockfd);

            //多进程
            // int pid=fork();
            // //child
            // if(pid==0)
            // {
            //     close(listensock_);
            //     //让子进程退出，把孙子进程挂到0号，进程结束自动释放资源
            //     if(pid>0)exit(0);
            //     Service(sockfd, clientip, clientport);
            //     exit(0);
            // }
            // //sockfd给子进程后，父进程关掉，防止一堆sockfd
            // close(sockfd);

            // pthread_t tid;
            // pthread_create(&tid,nullptr,Routine,new ThreadData(sockfd,ip_,port_,this));

            // version 4 --- 线程池版本
            Task t(sockfd, ip_, port_);
            ThreadPool<Task>::GetInstance()->Push(t);
        }
    }

    static void*Routine(void*args)
    {
        
        pthread_detach(pthread_self());
        ThreadData*td=static_cast<ThreadData*>(args);

        td->tsvr->Service(td->sockfd, td->clientip, td->clientport);
        delete td;
        return nullptr;
    }

    void Service(int sockfd, const std::string &clientip, const uint16_t &clientport)
    {
        // 测试代码
        char buffer[4096];
        while (true)
        {
            ssize_t n = read(sockfd, buffer, sizeof(buffer));
            if (n > 0)
            {
                buffer[n] = 0;
                std::cout << "client say# " << buffer << std::endl;
                std::string echo_string = "tcpserver echo# ";
                echo_string += buffer;

                write(sockfd, echo_string.c_str(), echo_string.size());
            }
            else if (n == 0)
            {
                lg(Info, "%s:%d quit, server close sockfd: %d", clientip.c_str(), clientport, sockfd);
                break;
            }
            else
            {
                lg(Warning, "read error, sockfd: %d, client ip: %s, client port: %d", sockfd, clientip.c_str(), clientport);
                break;
            }
        }
    }

private:
    int listensock_;
    uint16_t port_;
    std::string ip_;
};