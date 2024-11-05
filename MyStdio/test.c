#include<stdio.h>
#include"mystdio.h"
#include<string.h>


int main()
{
    _FILE* fp= _fopen("test.txt","a");
    if(fp==NULL)return 1;
    const char*msg="hello world\n";

    _fwrite(fp,msg,strlen(msg));
    _close(fp);

    return 0;
}
