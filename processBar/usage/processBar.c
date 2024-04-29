#include"processBar.h"

void processBar(int rate)
{
    if(rate<0||rate>100)
        return;
    static char str[MAX]={0};

    static const char rotate[]="|/-\\";
    size_t rotate_len =strlen(rotate);
    printf("[%-100s][%3d%%][%c]\r",str,rate,rotate[rate%rotate_len]);
    str[rate]=DISPLAY;
    ++rate;
    if(rate<TOTAL)
    {
        str[rate]='>';   
    }
    else if(rate>TOTAL)//rate==TOTAL的时候需要打印不能初始化，又不要'>'
    {
        memset(str,0,sizeof(str));
    }
    fflush(stdout);
}
