#include"log.hpp"

int main()
{
    Log log;
    int a=0;
    std::cin>>a;
    log.Enable(a);
    log(1,"hello:%d",1);
    return 0;
}
