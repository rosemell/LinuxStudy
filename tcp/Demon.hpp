#include <iostream>

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

std::string nullfile = "/dev/null";
void Demon(const std::string &pwd = "")
{
    // 1. 忽略其他异常信号
    signal(SIGCHLD, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGSTOP, SIG_IGN);

    // 2. 将自己变成独立的会话
    if (fork() > 0)
        exit(0); // 父进程自动退出
    setsid();

    // 3. 更改当前调用进程的工作目录
    if (!pwd.empty())
        chdir(pwd.c_str());

    // 4. 标准输入，标准输出，标准错误重定向至/dev/null
    int fd=open(nullfile.c_str(),O_RDWR);
    if(fd>0)
    {
        dup2(fd,0);
        dup2(fd,1);
        dup2(fd,2);
        close(fd);
    }
}