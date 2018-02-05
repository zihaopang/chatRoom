#include <stdlib.h> 
#include <termio.h>
#include <unistd.h>
#include <stdio.h> 
#include <signal.h>
#include <errno.h> 
#include <string.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sqlite3.h>

#include "/home/chat_room/include/all.h"

void func(int signal)
{
    if(signal == SIGINT)
    {
        printf("\n请在主界面输入EXT退出程序！\n");
    }
}

int input_order(int sockfd)
{
    char order[MAX_SIZE];
    extern struct message msg;
    
    signal(SIGINT,func);
    
    printf("\t\t\t\t\t请输入命令:\n\t\t\t\t\t");
    
    input_deal(order);
    
    if(!strcmp(order,"STO"))
    {
	private_chat(sockfd);
    }
    else if(!strcmp(order,"STA"))
    {
        group_chat(sockfd); 
    }
    else if(!strcmp(order,"DIS"))
    {
	display_users(sockfd);
    }
    else if(!strcmp(order,"HLP"))
    {
        system("reset"); 

	help_table();
	
	reset(sockfd);

    }
    else if(!strcmp(order,"EXT"))
    {
        exit(1);
    }
    else if(!strcmp(order,"CHP"))
    {
        change_passwd(sockfd);
    }
    else if(!strcmp(order,"SNF"))
    {
        send_file(sockfd);
    }
    else
    {
        system("reset");
	
	welcome_table();
	
	printf("\t\t\t\t\t请输入正确的指令,如有疑问请输入:HLP\n");
        
	input_order(sockfd);
    }

    return 0;
}
