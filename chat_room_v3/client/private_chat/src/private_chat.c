#include <curses.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int private_chat(char *user,int sockfd,int flag)
{
    int i;
    char sql[MAX_SIZE];
    extern char now_user[10];
    extern Content tables;
    extern struct message msg;
    
    strcpy(msg.name,(char *)now_user);
    strcpy(msg.toname,user);
    msg.action = STO;

    if(1 == flag)
    {
        echo();
        mvwgetnstr(tables.chat_win,18,2,msg.msg,45); 
        noecho();
    }
    else if(2 == flag)
    {
        msg.action = STA;
        
	echo();
        mvwgetnstr(tables.chat_win,18,2,msg.msg,45); 
        noecho();
    }

    mvwprintw(tables.chat_win,18,2,"                                               ");
    wbkgd(tables.chat_win,COLOR_PAIR(2));

    sprintf(sql,"%s[^_^]",msg.msg);
    
    mvwprintw(tables.chat_win,6 + tables.num,49 - strlen(sql),sql);
    
    tables.num++;

    wrefresh(tables.chat_win);

    write(sockfd,&msg,sizeof(struct message));
                                
    memset(sql,0,sizeof(sql));
    
    if(tables.num == 9)
    {
        for(i = 6; i < 15; i++)
	{
	    mvwprintw(tables.chat_win,i,1,"                                                ");
	}
        
	wbkgd(tables.chat_win,COLOR_PAIR(2));
        
	tables.num = 0;
    }
    
    memset(&msg,0,sizeof(struct message));

    return 0;
}
