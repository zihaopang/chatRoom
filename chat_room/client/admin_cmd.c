#include <stdio.h>
#include <signal.h>

#include "/home/chat_room/include/all.h"

int admin_cmd(int sockfd)
{
    char order[MAX_SIZE];
    
    printf("\t\t\t\t\t解禁(SAY)/禁言(NOS)/踢出(OUT)\n\t\t\t\t\t");
    scanf("%s",order);

    if(!strcmp(order,"SAY"))
    {
        say(sockfd); 
    }
    else if(!strcmp(order,"NOS"))
    {
	no_say(sockfd);
    }
    else if(!strcmp(order,"OUT"))
    {
        out(sockfd); 
    }
    else
    {
        system("reset");
        
	printf("\t\t\t\t\t请您输入正确的命令\n");
	
	admin_table();

	admin_cmd(sockfd);
    }
}
