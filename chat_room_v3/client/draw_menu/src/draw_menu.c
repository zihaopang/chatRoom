#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int draw_menu(int sockfd,WINDOW *win,int *num,char (*users)[10])
{
    int j;
    int i = 0;
    extern struct message msg;  
    
    setlocale(LC_ALL,"");

    msg.action = DIS;
    
    write(sockfd,&msg,sizeof(struct message));
    
    while(msg.action == DIS)
    {
        write(sockfd,&msg,sizeof(struct message));
    }
    
    while(*msg.users[i] != 0)
    {
	i++;
    } 
    
    *num = i;
    
    for(j = 0; j < i; j++)
    {
        mvwaddstr(win,9 + j,3,msg.users[j]);

	strcpy(users[j],msg.users[j]);

    }

    wrefresh(win);
    
    i = 0;
    
    memset(&msg,0,sizeof(struct message));
    
    return 0;
}
