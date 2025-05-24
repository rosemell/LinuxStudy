#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>
#include <unistd.h>
void Usage(const std::string &proc) { std::cout << "\n\rUsage: " << proc << " serverip serverport\n" << std::endl; }

// ./tcpclient serverip serverport
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }

    std::string ip = argv[1];
    int port = std::stoi(argv[2]);

    sockaddr_in serv;
    inet_pton(AF_INET, ip.c_str(), &serv.sin_addr.s_addr);
    serv.sin_port = htons(port);
    serv.sin_family = AF_INET;

    char buffer[1024];

    while (true)
    {
        size_t cnt = 5;
        bool isconnect = false;
        int sockfd = 0;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            std::cerr << "socket error" << std::endl;
            return 1;
        }
        do
        {
            int n = connect(sockfd, (sockaddr *)&serv, sizeof(serv));
            if (n < 0)
            {
                --cnt;
                isconnect= true;
            }
            else
            {
                break;
            }
        } while (isconnect && cnt);


        if (cnt == 0)
        {
            std::cerr << "user offline..." << std::endl;
            break;
        }
        std::string message;
        std::getline(std::cin, message);
        message += "\n";
        int n = write(sockfd, message.c_str(), message.size());
        if (n < 0)
        {
            std::cerr << "write error..." << std::endl;
        }
        n = read(sockfd, buffer, 1024 - 1);
        if (n < 0)
        {
            std::cerr << "read error" << std::endl;
            //exit(1);
        }
        buffer[n] = 0;
        std::cout << buffer << std::endl;

        close(sockfd);
    }

    return 0;
}