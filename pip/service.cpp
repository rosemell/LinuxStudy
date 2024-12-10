#include"comm.hpp"


int main()
{
    Log log;
    Init init;//用init的构造和析构函数创建和删除FIFO文件
    int fd=open(FIFO_FILE, O_RDONLY);
    if(fd<0)
    {
        log(Fatal, "FIFO_FILE open error, error string: %s, error code: %d", strerror(errno), errno);
        exit(FIFO_OPEN_ERR);
    }
    while(true)
    {
        char buf[BUF_SIZE];
        int n=read(fd,buf,sizeof(buf));
        if(n>0)
        {
            buf[n]=0;
            
            std::cout << "client say# " << buf << std::endl;
        }
        else if(n==0)
        {
            log(Debug, "client quit, me too!, error string: %s, error code: %d", strerror(errno), errno);
            break;
        }
        else
        {
            break;
        }
    }
    close(fd);
    return 0;

}

