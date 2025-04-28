#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <functional>
#include <string.h>
#include <string>

#include "Log.hpp"
const size_t defaultport = 8080;
const std::string defaultip = "0.0.0.0";
const int size = 1024;

extern Log lg;

// using func_t=std::function<std::string(const std::string&)>;
typedef std::function<std::string(const std::string &)> func_t;

enum
{
    SOCKET_ERR = 1,
    BIND_ERR
};

class UdpServer
{
  public:
    UdpServer(size_t port = defaultport, std::string ip = defaultip)
        : ip_(ip), port_(port), sockfd_(0), isrunning_(false)
    {
    }
    void Init()
    {
        sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd_ < 0)
        {
            lg(Fatal, "socket create error, sockfd: %d", sockfd_);
            exit(SOCKET_ERR);
        }
        lg(Info, "socket create success, sockfd: %d", sockfd_);

        // 绑定
        sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET; // 给系统看，不需要转换
        local.sin_port = htons(port_);
        // inet_addr自动将结果转换为网络字节序
        local.sin_addr.s_addr = inet_addr(ip_.c_str());
        // local.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(sockfd_, (const struct sockaddr *)&local, sizeof(local)) < 0)
        {
            lg(Fatal, "bind error, errno: %d, err string: %s", errno, strerror(errno));

            exit(BIND_ERR);
        }
        std::cout<<"port:"<<ntohs(local.sin_port)<<"   ip:"<<ntohl(local.sin_addr.s_addr)<<std::endl;
        lg(Info, "bind success, errno: %d, err string: %s", errno, strerror(errno));
    }

    void Run(func_t func)
    {
        isrunning_ = true;
        char inbuffer[size];
        while (isrunning_)
        {
            sockaddr_in client;
            socklen_t len = sizeof(client);
            ssize_t n = recvfrom(sockfd_, inbuffer, sizeof(inbuffer) - 1, 0, (sockaddr *)&client, &len);
            std::cout<<"recvfrom seccess"<<std::endl;
            if (n < 0)
            {
                lg(Warning, "recvfrom error, errno: %d, err string: %s", errno, strerror(errno));
                continue;
            }
            inbuffer[n] = 0;
            std::string info = inbuffer;
            std::string echo_string = func(info);
            //std::cout<<echo_string;
            sendto(sockfd_, echo_string.c_str(), echo_string.size(), 0, (sockaddr *)&client, len);
        }
    }
    ~UdpServer()
    {
        if (sockfd_ > 0)
        {
            close(sockfd_);
        }
    }

  private:
    int sockfd_;     // 网路文件描述符
    std::string ip_; // 任意地址bind 0
    uint16_t port_;  // 表明服务器进程的端口号
    bool isrunning_;
};