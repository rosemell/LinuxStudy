#include"comm.hpp"


int main()
{
    int id=CreateShm();
    printf("id:%d\n",id);
    char*p=(char*)shmat(id,nullptr,0);
    if(p==(void*)-1)
    {
        log(Error,"shmat erro");
        exit(1);
    }
    log(Debug,"shmat success");
    shmdt(p);
    log(Debug,"shmdt Success");
    shmctl(id,IPC_RMID,nullptr);
    log(Debug,"Destroy ShareMem:%d Success",id);
    return 0;
}