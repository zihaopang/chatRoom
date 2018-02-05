#include <stdio.h>
#include <time.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

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
	
        *msg.msg = 0;

	msg.action = 0;

	read(sockfd,&msg,sizeof(struct message));
    }

    if(msg.action == SNF_END)
    {
	fputs("\n",fp);

	sprintf(sql,"您有来自用户%s的邮件",msg.name);

	remind(sql);
        
	memset(sql,0,sizeof(sql));

        memset(&msg,0,sizeof(struct message));
    }

    return 0;
}
