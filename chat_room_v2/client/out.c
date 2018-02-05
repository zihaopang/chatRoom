#include <stdio.h>

#include "/home/chat_room/include/all.h"

int out(int sockfd)
{
    extern struct message msg;
    
    system("reset");

    msg.action = OUT;

    printf("/---------------管理员界面---------------/\n\n");
    printf("请输入需要踢出的用户姓名:\n");
    scanf("%s",msg.name);

    write(sockfd,&msg,sizeof(struct message));

    admin_reset();

    return 0;
}
