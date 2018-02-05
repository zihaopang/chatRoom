#include <stdlib.h> 
#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sqlite3.h>

#include "/home/chat_room/include/all.h"

char* getPasswd()
{
    char ch;
    int i = 0;
    static char p[MAX_LEN+1]="";
    
    while((ch = getch())!= -1 && ch != ENTER)
    {
         if(i == MAX_LEN && ch != BACKSPACE)
         {
              putchar(ALARM);
              continue;
         }
         else
         {
             p[i] = ch;
             putchar('*');
             i++;
         }
    }
    if(ch == -1)
    {
        while(i != -1)
        {
            p[i--] = '\0';
        }
        return NULL;
    }
    
    p[i]='\0';
    
    return p;
}

int getch()
{
        struct termios tm, tm_old;
        int fd = STDIN_FILENO, c;
        if(tcgetattr(fd, &tm) < 0)
                return -1;
        tm_old = tm;
        cfmakeraw(&tm);
        if(tcsetattr(fd, TCSANOW, &tm) < 0)
                return -1;
        c = fgetc(stdin);
        if(tcsetattr(fd, TCSANOW, &tm_old) < 0)
                return -1;
        return c;
}

int passwd_judge(int sockfd)
{
    char input[MAX_SIZE];
    char order[MAX_SIZE];
    extern struct message msg;

    printf("\t\t\t\t\t登录(LOG)/注册(REG):\n\t\t\t\t\t");
    
    input_deal(order);

    if(!strcmp(order,"REG"))
    {
        msg.action = LOGIN;

	printf("\t\t\t\t\t请输入新用户的用户名(小于20字节):\n\t\t\t\t\t");
        
	scanf("%[^\n]",msg.name);
	
	while(strlen(msg.name) > 20)
	{
	    printf("\t\t\t\t\t用户名过长！请重新输入！:");
	    memset(msg.name,0,sizeof(msg.name));
	    getchar();
            scanf("%[^\n]",msg.name);
	}

	printf("\t\t\t\t\t请输入新用户的密码(小于10字节):\n\t\t\t\t\t");
	getchar();
	strcpy(msg.passwd,getPasswd());
    }
    else if(!strcmp(order,"LOG"))
    {
        msg.action = LOG;
        
	printf("\t\t\t\t\t请输入用户名或id:\n\t\t\t\t\t");
       
	scanf("%[^\n]",input);
	
	if((input[0] >= '1') && (input[0] <= '9'))
	{
	    msg.id = atoi(input);
	}
	else
	{
	    strcpy(msg.name,input);
	}

	while(strlen(msg.name) > 20)
	{
	    printf("\t\t\t\t\t用户名过长！请重新输入！:");
	    memset(msg.name,0,sizeof(msg.name));
	    getchar();
            scanf("%[^\n]",msg.name);
	}

	printf("\t\t\t\t\t请输入用户密码:\n\t\t\t\t\t");
	getchar();
	strcpy(msg.passwd,getPasswd()); 
    }
    else
    {
        system("reset");
        
        passwd_table();

	printf("\t\t\t\t\t请输入正确的指令\n");

	passwd_judge(sockfd);
    }
    
    if(msg.action == LOG || msg.action == LOGIN)
    {
        write(sockfd,&msg,sizeof(struct message));

        read(sockfd,&msg,sizeof(struct message));
    }
    
    return 0;
}
