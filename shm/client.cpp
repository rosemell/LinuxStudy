#include"comm.hpp"


int main()
{
    int id=GetShm();
    char*shmaddr=(char*)shmat(id,nullptr,0);
    //通信部分
    while(1)
    {
        std::cout<<"please Enter@";
        std::fgets(shmaddr,MemSize,stdin);
    }
    shmdt(shmaddr);
    return 0;
}