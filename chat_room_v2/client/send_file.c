#include <stdio.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

void send_file(int sockfd)
{
    FILE *fp;
    char file_name[MAX_SIZE];
    extern struct message msg;

    system("reset");

    printf("/---------------发送文件界面---------------\n");
    
    printf("请输入收件人:");
    scanf("%s",msg.toname);
    printf("请输入文件名:");
    scanf("%s",file_name);
    
    msg.action = SNF;

    msg.id = 1;

    write(sockfd,&msg,sizeof(struct message));
    
    sleep(1);
    
    if(msg.action == SNF_FAIL)
    {
	printf("用户%s不在线！\n",msg.toname);
		
        memset(&msg,0,sizeof(struct message));
    }
    else
    {
        fp = fopen(file_name,"a+");
        
	msg.id = 0;

	
	while(!feof(fp))
        {
	    msg.msg[1024] = 0;
            
	    strcpy(msg.users[0],file_name);
             
	    if(fgets(msg.msg,1024,fp) != NULL)
	    {
	        write(sockfd,&msg,sizeof(struct message));
	    }

        }
        
	msg.action = SNF_END;

	write(sockfd,&msg,sizeof(struct message));
    }

    reset(sockfd);
}
