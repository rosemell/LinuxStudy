#pragma once

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include"log.hpp"

#define FIFO_FILE "./myfifo"
#define MODE 0664
#define BUF_SIZE 1024

Log mylog;

enum
{
    FIFO_CREATE_ERR = 1,
    FIFO_DELETE_ERR,
    FIFO_OPEN_ERR
};

class Init{
    public:
    Init()
    {
        umask(0);
        int n=mkfifo(FIFO_FILE,MODE);
        if(n<0)
        {
            mylog(Fatal,"mkfifo erro");
            // exit(FIFO_CREATE_ERR);
            //有可能已经创建了，所以不急着退
        }

    }

    ~Init()
    {
        int n=unlink(FIFO_FILE);
        if(n<0)
        {
            mylog(Error,"FIFO_FILE unlink error");
            exit(FIFO_DELETE_ERR);
        }
    }
};