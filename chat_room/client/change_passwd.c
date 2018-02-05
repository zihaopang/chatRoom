#include <stdio.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

int change_passwd(int sockfd)
{
    system("reset");

    extern struct message msg;
    msg.action = CHP;

    printf("/---------------修改密码界面---------------\n");

    printf("请输入原密码(小于10位):\n");
    scanf("%s",msg.passwd);

    printf("请输入新密码(小于10位):\n");
    scanf("%s",msg.msg);
    
    if((strlen(msg.passwd) > 10) || (strlen(msg.msg) > 10))
    {
        printf("密码长度过长，请重新输入！\n");

	change_passwd(sockfd);
    }
    else
    {
	write(sockfd,&msg,sizeof(struct message));
    }

    sleep(1);

    reset(sockfd);
}
