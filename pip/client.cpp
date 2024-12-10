#include"comm.hpp"

#include<iostream>
int main()
{
    Log log;
    int fd=open(FIFO_FILE, O_WRONLY);
    if(fd<0)
    {
        log(Fatal, "FIFO_FILE open error, error string: %s, error code: %d", strerror(errno), errno);
        exit(FIFO_OPEN_ERR);
    }
    std::cout << "client open file done" << std::endl;
    std::string line;
    while(true)
    {
        std::cout << "Please Enter@ ";
        std::getline(std::cin, line);
        
        write(fd,line.c_str(),line.size());
    }
    close(fd);
    return 0;
}
