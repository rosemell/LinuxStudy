#include <fstream>
#include <string>
#include"Log.hpp"
#include <unordered_map>
const std::string dictname = "./dict.txt";
const std::string sep = ":";

static bool split(const std::string &s, std::string &split1, std::string &split2) 
{
    auto pos=s.find(sep);
    if(pos == std::string::npos) return false;
    split1=s.substr(0,pos);
    split2=s.substr(pos+1);
    return true;
}
class Init
{
  public:
    Init()
    {
        std::ifstream in(dictname);
        std::string line;
        std::string split1, split2;
        if(!in.is_open())
        {
            lg(Fatal, "ifstream open %s error", dictname.c_str());
            exit(1);
        }
        while(std::getline(in, line))
        {
            split(line,split1,split2);
            dict.insert({split1,split2});
        }
        in.close();
    }
    std::string translation(const std::string &key)
    {
        auto iter = dict.find(key);
        if(iter == dict.end()) return "Unknow";
        else return iter->second;
    }
  private:
    std::unordered_map<std::string, std::string> dict;
};