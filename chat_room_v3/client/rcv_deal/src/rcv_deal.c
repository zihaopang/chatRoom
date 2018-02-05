#include <curses.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int rcv_deal()
{
    int i;
    char sql[MAX_SIZE];
    extern Content tables;
    extern struct message msg;

    if(strcmp(msg.name,tables.name) != 0)
    {
        sprintf(sql,"%s:%s",msg.name,msg.msg);
                    
	remind(sql);
    }
    else
    {
	sprintf(sql,"[^_^]%s",msg.msg);

        mvwaddstr(tables.chat_win,6 + tables.num,1,sql);

        tables.num++;

        wrefresh(tables.chat_win);
    }
		
    memset(sql,0,sizeof(sql));
    memset(&msg,0,sizeof(struct message));
    
    if(tables.num == 9)
    {
        for(i = 6; i < 15; i++)
	{
	    mvwprintw(tables.chat_win,i,1,"                                                ");
	}
        
	wbkgd(tables.chat_win,COLOR_PAIR(2));
        
	tables.num = 0;
    }
    
    return 0;
}
