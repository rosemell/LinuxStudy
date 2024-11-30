#include"log.hpp"

int main()
{
    log log1;
    int a=0;
    std::cin>>a;
    log1.Enable(a);
    log1(1,"hello:%d",1);
    return 0;
}