#include<stdio.h>
#include<string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include"log.hpp"


Log log;
const int MemSize=4096;
const std::string pathname="./service.exe";
const int proj_id=0x6666;
key_t GetKey()
{
    key_t k=ftok(pathname.c_str(),proj_id);
    if(k<0)
    {
        log(Error,"ftok");
        exit(1);
    }
    log(Info,"ftok success");
    return k;
}


int GetShareMemHelper(int flag)
{
    key_t k = GetKey();
    int shmid = shmget(k, MemSize, flag);
    if(shmid < 0)
    {
        log(Fatal, "create share memory error: %s", strerror(errno));
        exit(2);
    }
    log(Info, "create share memory success, shmid: %d", shmid);

    return shmid;
}

int CreateShm()
{
    return GetShareMemHelper(IPC_CREAT | IPC_EXCL | 0666);
}

int GetShm()
{
    return GetShareMemHelper(IPC_CREAT); 
}