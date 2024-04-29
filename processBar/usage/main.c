#include"processBar.h"
#include<unistd.h>

typedef void (*call_back)(int); 

void downlaod(call_back cb)
{
    int cnt=0;
    int total=2000;//假设要下载2000M内容
    while(cnt<=total)
    {
        cb(cnt*100/total);
        
        cnt+=10;  //模拟下载
        usleep(50000);
    }
    printf("\n");
}
int main()
{
    printf("downlaod1:\n");
    downlaod(processBar);
    printf("downlaod2:\n");
    downlaod(processBar);
    printf("downlaod3:\n");
    downlaod(processBar);
    printf("downlaod4:\n");
    downlaod(processBar);
    return 0;
}
