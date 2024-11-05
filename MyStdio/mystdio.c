#include"mystdio.h"

_FILE* _fopen(const char *file,const char*flag)
{
    int mod=-1;
    if(strcmp(flag,"w")==0)
    {
        mod=(O_CREAT|O_WRONLY|O_TRUNC);
    }
    else if(strcmp(flag,"a")==0)
    {
        mod=(O_CREAT|O_WRONLY|O_APPEND);
    }
    else if(strcmp(flag,"r")==0)
    {
        mod=O_RDONLY;
    }
    else 
    {
        return NULL;
    }
    if(mod==-1) return NULL;
    
    umask(0);
    _FILE *ret=malloc(sizeof(_FILE));
    
    if(ret==NULL)   return NULL;
    
    ret->fd=open(file,mod,0666);
    memset(ret->bf,0,sizeof(ret->bf));
    return ret;
}
_FILE* _fwrite(_FILE*fp,const char *msg,int n)
{
    memcpy( (fp->bf+fp->n) ,msg,n*sizeof(*msg));
    fp->n+=n;

    write(fp->fd,fp->bf,fp->n);
    fp->n=0;

    return fp;
}
int _fflush(_FILE*fp)
{
    write(fp->fd,fp->bf,fp->n);
    fp->n=0;
    return 0;
}
void _close(_FILE*fp)
{
    _fflush(fp);
    close(fp->fd);
    free(fp);
}
