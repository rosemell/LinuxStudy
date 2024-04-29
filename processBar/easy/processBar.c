#include"processBar.h"

void processBar()
{
    char rotate[]="|/-\\";
    size_t rotate_len =strlen(rotate);
    char str[MAX]={0};
    int cnt=0;
    while(cnt<=TOTAL)
    {
        printf("[%-100s][%d%%]%c\r",str,cnt,rotate[cnt%rotate_len]);
        str[cnt]=DISPLAY;
        ++cnt;
        if(cnt<TOTAL)str[cnt]='>';
        
        fflush(stdout);
        usleep(50000);
    }
    printf("\n");
}
