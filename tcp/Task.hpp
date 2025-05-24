#pragma once
#include"Log.hpp"
#include <string>
#include"Init.hpp"

enum{
    DivZero=1,
    ModZero,
    Unknown
};

static Init init;
class Task
{
public:
    Task(int sockfd, const std::string &clientip, const uint16_t &clientport) 
    :sockfd_(sockfd)
    ,clientip_(clientip)
    ,clientport_(clientport)
    {}
    void run()
    {
        char buffer[4096];
        ssize_t n = read(sockfd_, buffer, sizeof(buffer));
        if (n > 0)
        {
            buffer[n-1] = 0;
            std::cout << "client say# " << buffer << std::endl;
            //std::string echo_string = "tcpserver echo# ";
            //echo_string += buffer;
            std::string echo_string=init.translation(buffer);
            write(sockfd_, echo_string.c_str(), echo_string.size());
        }
        else if (n == 0)
        {
            lg(Info, "%s:%d quit, server close sockfd: %d", clientip_.c_str(), clientport_, sockfd_);
        }
        else
        {
            lg(Warning, "read error, sockfd: %d, client ip: %s, client port: %d", sockfd_, clientip_.c_str(), clientport_);
        }
        close(sockfd_);
        std::cout<<"close success"<<std::endl;
    }
    void operator ()()
    {
        run();
    }
    ~Task()
    {
    }

private:
    int sockfd_;
    const std::string &clientip_;
    const uint16_t &clientport_;
};