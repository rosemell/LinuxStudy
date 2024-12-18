#include"comm.hpp"


int main()
{
    int id=CreateShm();
    char*shmaddr=(char*)shmat(id,nullptr,0);
    //通信部分
    while(1)
    {
        std::cout<<"clientsay@:"<<shmaddr<<std::endl;
        sleep(1);
    }
    shmdt(shmaddr);
    shmctl(id,IPC_RMID,nullptr);
    return 0;
}