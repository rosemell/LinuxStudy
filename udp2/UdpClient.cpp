#include <arpa/inet.h>
#include <cstddef>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include<iostream>
#include<string>
#include <sys/types.h>
#include<pthread.h>
using std::cout;
using std::endl;
void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " serverip serverport\n"<< std::endl;
}

struct ThreadData
{
    struct sockaddr_in server;
    int sockfd;
    std::string serverip;
};

void *recv_message(void *args)
{
    ThreadData*td=static_cast<ThreadData*>(args);
    char buffer[1024];
    while(true)
    {
        sockaddr_in tmp;
        socklen_t len=sizeof(tmp);
        size_t s=recvfrom(td->sockfd,buffer,sizeof(buffer)-1,0,(sockaddr*)&tmp,&len);
        
        if(s>0)
        {
            buffer[s] = 0;
            std::cerr << buffer << endl;
        }
    }
    return nullptr;
}
void *send_message(void *args)
{
    ThreadData*td=static_cast<ThreadData*>(args);
    std::string message;

    //注册 登录提示
    std::string welcome = td->serverip;
    welcome += " comming...";
    sendto(td->sockfd, welcome.c_str(), welcome.size(), 0
        ,(struct sockaddr *)&(td->server), sizeof(td->server));
    
    while(true)
    {
        cout << "Please Enter@ ";

        std::getline(std::cin,message);
        sendto(td->sockfd,message.c_str(),message.size(),0
            ,(sockaddr*)&td->server,sizeof(td->server));
    }
}

int main(int argc,char*argv[])
{
    if(argc!=3)
    {
        Usage(argv[0]);
        exit(0);
    }
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd < 0)
    {
        cout << "socker error" << endl;
        return 1;
    }
    sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_port=htons(std::stoi(argv[2]) );
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_family=AF_INET;

    ThreadData td={server,sockfd,argv[2]};
    
    pthread_t p_serv,p_send;
    pthread_create(&p_send,nullptr,send_message,&td);
    pthread_create(&p_serv,nullptr,recv_message,&td);

    pthread_join(p_send,nullptr);
    pthread_join(p_serv,nullptr);

    // client 要bind吗？要！只不过不需要用户显示的bind！一般有OS自由随机选择！
    // 一个端口号只能被一个进程bind，对server是如此，对于client，也是如此！
    // 其实client的port是多少，其实不重要，只要能保证主机上的唯一性就可以！
    // 系统什么时候给我bind呢？首次发送数据的时候

    // std::string message;
    // char buffer[1024];
    // while(true)
    // {
    //     cout << "Please Enter@ ";
    //     std::getline(std::cin, message);
    //     sendto(sockfd,message.c_str(),message.size(),
    //     0,(sockaddr*)&server,sizeof(server));

    //     struct sockaddr_in temp;
    //     socklen_t len = sizeof(temp);
    //     ssize_t n=recvfrom(sockfd,buffer,1024-1,0,(sockaddr*)&temp,&len);
    //     buffer[n]=0;
    //     cout<<buffer<<endl;
    // }

    return 0;
}