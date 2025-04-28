#include <arpa/inet.h>
#include <cstddef>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include<iostream>
#include<string>
#include <sys/types.h>
using std::cout;
using std::endl;
void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " serverip serverport\n"<< std::endl;
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


    // client 要bind吗？要！只不过不需要用户显示的bind！一般有OS自由随机选择！
    // 一个端口号只能被一个进程bind，对server是如此，对于client，也是如此！
    // 其实client的port是多少，其实不重要，只要能保证主机上的唯一性就可以！
    // 系统什么时候给我bind呢？首次发送数据的时候

    std::string message;
    char buffer[1024];
    while(true)
    {
        cout << "Please Enter@ ";
        std::getline(std::cin, message);
        sendto(sockfd,message.c_str(),message.size(),
        0,(sockaddr*)&server,sizeof(server));

        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        ssize_t n=recvfrom(sockfd,buffer,1024-1,0,(sockaddr*)&temp,&len);
        buffer[n]=0;
        cout<<buffer<<endl;
    }

    return 0;
}