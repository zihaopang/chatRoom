#include <stdio.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

int display_users(int sockfd)
{
    int i = 0;
    extern char now_user[10];
    extern struct message msg;  
    
    msg.action = DIS;
         
    write(sockfd,&msg,sizeof(struct message));
    
    while(msg.action == DIS)
    {
        write(sockfd,&msg,sizeof(struct message));
    }
    
    system("reset");
    
    printf("当前在线用户:\n");
     
    while(*msg.users[i] != 0)
    {
        printf("用户%d:%s\n",i+1,msg.users[i]);
	
	i++;
    }

    printf("当前操作用户:%s\n",now_user);
    
    memset(&msg,0,sizeof(struct message));

    reset(sockfd);

    return 0;
}
