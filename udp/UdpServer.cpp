#include"UdpServer.hpp"
#include <cinttypes>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include<vector>
Log lg;

std::string Handler(const std::string &str)
{
    std::string res = "Server get a message: ";
    res += str;
    std::cout << res << std::endl;

    // pid_t id = fork();
    // if(id == 0)
    // {
    //     // ls -a -l -> "ls" "-a" "-l"
    //     // exec*();
    // }
    return res;
}
bool SafeCheck(const std::string &cmd)
{
    std::vector<std::string> key_word = {
        "rm",
        "mv",
        "cp",
        "kill",
        "sudo",
        "unlink",
        "uninstall",
        "yum",
        "top",
        "while"
    };
    for(auto &word : key_word)
    {
        auto pos = cmd.find(word);
        if(pos != std::string::npos) return false;
    }

    return true;
}
std::string ExcuteCommand(const std::string &cmd)
{
    std::cout << "get a request cmd: " << cmd << std::endl;
    if(!SafeCheck(cmd)) return "Bad man";
    FILE*fp=popen(cmd.c_str(),"r");
    std::string result;
    char buffer[4096];
    while(true)
    {
        char*ok=fgets(buffer, sizeof(buffer), fp);
        if(nullptr==ok)break;
        result+=ok;
    }
    return result;
}
int main() {
    size_t port=20000;
    std::unique_ptr<UdpServer> svr(new UdpServer(port));

    svr->Init();
    svr->Run(ExcuteCommand);
    return 0;
}
