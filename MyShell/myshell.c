#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>


#define LEFT "["
#define RIGHT "]"
#define LABEL "#"
#define LINE_SIZE 64
#define SPCH " "


char*envirenment;
char commandline[LINE_SIZE];
char pwd[LINE_SIZE];
char cline[LINE_SIZE][LINE_SIZE];
char *sp_ret[LINE_SIZE]={};

const char*getusername()
{
    return getenv("USER");
}
const char*mygethostname()
{
    return getenv("HOSTNAME");
}
const char*getpwd()
{
    getcwd(pwd,sizeof(pwd));
    return pwd;
}

void interact()
{
    printf(LEFT"%s@%s %s"RIGHT""LABEL,getusername() ,mygethostname(),getpwd());
    char*s=fgets(commandline,sizeof(commandline),stdin);
    assert(s);
    commandline[strlen(commandline)-1]='\0';
    //如果s被定义却没有使用，编译器可能会报错
    //这句随便用下s防止编译器报错
    (void*)s;
}
void split(char*s)
{
    sp_ret[0]=s;
    sp_ret[1]=strtok(s,SPCH);
    int i=1;
    while(sp_ret[i++]=strtok(NULL,SPCH))
    {
        ;
    }
}
void execlerro()
{
    fflush(stderr);
    perror("system:");
    fprintf(stderr,"execvp error ## error command:");
    int i=0;
    for(i=0;sp_ret[i];++i)
    {
        fprintf(stderr,"%s ",sp_ret[i]);
    }
    fprintf(stderr,"\n");
}
void outcommand()
{
    int ppid=fork();
    //子进程
    if(0==ppid)
    {
       execvp(sp_ret[0],sp_ret); 
       execlerro();//如果execvp系列执行成功那就不会执行这样一行，因为程序被替换了
    }
    else if(ppid>0)
    {
        int a[LINE_SIZE];
        wait(a);
        
    }
    else if(ppid==-1)
    {
        perror("fork erro");
    }
}
void command()
{
    static char exarg[LINE_SIZE];//当外部命令需要额外的参数时，用来传参
    strcpy(exarg,"");//初始化
    
    if(strcmp(sp_ret[0],"cd")==0)
    {
        chdir(sp_ret[1]);
        setenv("pwd",getpwd(),1);

        return;
    }
    else if(strcmp(sp_ret[0],"ls")==0)//这里并不是内建命令只是需要加一些额外的参数
    {
        char**tmp=sp_ret;
        while(*++tmp)//找到sp_ret=NULL的地址
        {
            ;
        }

        strcpy(exarg,"--color");
        *tmp=exarg;
        //strcpy(*tmp,"--color");
        *++tmp=NULL;
        
    }
    outcommand();
}
//[wda@VM-12-2-centos MyShell]$
int main()
{
    while(1)
    {
        interact();
        //printf("%s\n",commandline);
        
        split(commandline);
        int i=0;
        for(i=0;sp_ret[i];++i)
        {
            //printf("%s\n",sp_ret[i]);
        }
        command();
    }
    return 0;
}


