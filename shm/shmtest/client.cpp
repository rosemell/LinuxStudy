#include"comm.hpp"


int main()
{
    int id=GetShm();
    log(Debug,"GetShm:%d",id);
    if(id==-1)
    {
        log(Error,"GetKey Error");
        exit(1);
    }
    char*p=(char*)shmat(id,nullptr,0);
    if(p==(void*)-1)
    {
        log(Error,"shmat erro,%s",strerror(errno));
        exit(1);
    }

    int a;
    scanf("%d",&a);
    log(Debug,"shmat success");
    shmdt(p);
    log(Debug,"shmdt Success");
    shmctl(id,IPC_RMID,nullptr);
    log(Debug,"Destroy ShareMem:%d Success",id);
    return 0;
}