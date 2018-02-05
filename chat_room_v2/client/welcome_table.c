#include <stdio.h>

int welcome_table()
{
    extern char now_user[10];

    printf("\n\t\t\t\t\t当前用户:%s\n",now_user);

    printf("\n\t\t\t\t\t\033[0;34m<------------------------------------------------------->\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                        欢迎归来！                     >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<         STO:私聊                   STA:群发           >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<         DIS:查看当前用户           HLP:帮助(短语)     >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<         EXT:退出                   CHP:修改密码       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<         SNF:发送文件                                  >\033[0m\n");
    printf("\t\t\t\t\t\033[1;34m<                                                       >\033[0m\n");
    printf("\t\t\t\t\t\033[0;34m<------------------------------------------------------->\033[0m\n");
    
    return 0;
}
