#include <stdio.h>
#include <time.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

int get_file(int sockfd)
{
    FILE *fp;
    time_t timep;
    char sql[1024];
    extern struct message msg;
    
    time(&timep);
    
    sprintf(sql,"%s_%s",msg.name,msg.users[0]);
 
    fp = fopen(sql,"a+");
    
    memset(sql,0,sizeof(sql));
    
    sprintf(sql,"INOFR\n--------------------------------------------------\nfrom:%s time:%sCONTENTS\n--------------------------------------------------\n",msg.name,ctime(&timep));
    
    fputs(sql,fp);

    while(msg.action == SNF)
    {
	fputs(msg.msg,fp);
	
	memset(&msg,0,sizeof(struct message));

	read(sockfd,&msg,sizeof(struct message));
    }
    
    if(msg.action == SNF_END)
    {
	fputs("\n",fp);

	printf("\n\t\t\t\t\t您有来自用户%s的邮件，请查收\n\t\t\t\t\t",msg.name);

        memset(&msg,0,sizeof(struct message));
    }

}
