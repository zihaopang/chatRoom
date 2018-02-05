#include <stdio.h>
#include <string.h>

int short_msg(char *infor,char *sh_msg)
{
    strcpy(sh_msg,infor);

    if(!strcmp(sh_msg,"WEL"))
    {
        strcpy(sh_msg,"欢迎来到我们聊天室");
    }
    else if(!strcmp(sh_msg,"MIS"))
    {
        strcpy(sh_msg,"好久不见");
    }
    else if(!strcmp(sh_msg,"SOR"))
    {
        strcpy(sh_msg,"非常抱歉……");
    }
    else if(!strcmp(sh_msg,"CLVR"))
    {
        strcpy(sh_msg,"你好聪明！");
    }
    
    return 0;
}
