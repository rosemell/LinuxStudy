#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

// 日志类型
#define Info 0
#define Debug 1
#define Warning 2
#define Error 3
#define Fatal 4

#define Screen 1
#define Onefile 2
#define Classfile 3

#define LogFile "log.txt"

#define SIZE 1024

class Log
{
public:
    Log()
    {
        _printMethod=Screen;
        _path="./log/";
    }
    ~Log()
    {
    }
    std::string levelToString(int level)
    {
        switch (level)
        {
        case Info:
            return "Info";
        case Debug:
            return "Debug";
        case Warning:
            return "Warning";
        case Error:
            return "Error";
        case Fatal:
            return "Fatal";
        default:
            return "None";
        }
    }
    void printOneFile(const std::string& logfile, const std::string&logtxt)
    {
        umask(0);
        // 设置权限：rwxrwxrwt (sticky bit)
        mkdir(_path.c_str(),0775);
        mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO | S_ISVTX;
        chmod(_path.c_str(),mode);
        std::string file=_path+logfile;
        int fd=open(file.c_str(),O_WRONLY|O_CREAT,0775);
        if(fd<0)
        {
            perror("打开或创建文件失败");
            return;
        }
        write(fd,logtxt.c_str(),logtxt.size());
        close(fd);
    }

    void printClassFile(int level, char*logtxt)
    {
        printOneFile("log.txt."+levelToString(level),logtxt);
    }

    void operator()(int level,const char*format,...)
    {

        // 固定格式
        char left[_size];


        time_t t=time(nullptr);
        tm*ctime=localtime(&t);
        snprintf(left,sizeof(left),
        "[%s][%d-%d-%d %d:%d:%d]",levelToString(level).c_str(),
                                ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,
                                ctime->tm_hour,ctime->tm_min,ctime->tm_sec);

        va_list s;
        va_start(s,format);
        char right[_size];
        vsnprintf(right,sizeof(left),format,s);
        va_end(s);
        
        char logtxt[2*_size];
        snprintf(logtxt, sizeof(logtxt), "%s %s\n", left, right);
        
        switch (_printMethod)
        {
        case Screen:
            std::cout<<logtxt;
            break;
        case Onefile:
            printOneFile(LogFile, logtxt);
            break;
        case Classfile:
            printClassFile(level, logtxt);
            break;     
        default:
            perror("日志文件类型选择错误");
            break;
        }
        // std::cout<<left<<right;
    }
    
    void Enable(char printMethod)
    {
        _printMethod=printMethod;
    }
private:
    char _printMethod;
    std::string _path;
    size_t _size=SIZE;
};
