#ifndef _MYSTDIO_H_
#define _MYSTDIO_H_ 

#include<sys/types.h>
#include<stdlib.h>
#include <fcntl.h>
#include<unistd.h>

#include<string.h>

#define BF_MAX 60
typedef struct _FILE{
    int fd;
    char bf[BF_MAX];
    int n;
}_FILE;

_FILE* _fopen(const char *file,const char*mod);
_FILE* _fwrite(_FILE*fp,const char *msg,int n);
int _fflush(_FILE*fp);
void _close(_FILE*fp);

#endif
