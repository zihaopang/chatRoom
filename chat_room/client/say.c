#include <stdio.h>

#include "/home/chat_room/include/all.h"

int say(int sockfd)
{
    extern struct message msg;

    msg.action = SAY;
    
    system("reset");

    printf("/---------------管理员界面---------------\n\n");

    printf("请输入需要被解禁的用户名:\n");
    scanf("%s",msg.name);

    write(sockfd,&msg,sizeof(struct message));

    admin_reset();

    return 0;
}
