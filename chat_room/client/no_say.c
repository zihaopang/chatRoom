#include <stdio.h>

#include "/home/chat_room/include/all.h"

int no_say(int sockfd)
{
    extern struct message msg;
    
    system("reset");
    
    msg.action = NO_SAY;

    printf("/---------------管理员界面---------------\n\n");
  
    printf("请输入需要被禁言的用户:");
    scanf("%s",msg.name);

    write(sockfd,&msg,sizeof(struct message));

    admin_reset(sockfd);
}
