#include <curses.h>
#include <locale.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int report_choice_7(int mousex,int mousey)
{
    int starty = (LINES - 24)/2 + 6;

    if(mousey == starty + 1)
    {
        return 1;
    }
    else if(mousey == starty + 2)
    {
        return 2;
    }
    else if(mousey == starty + 3)
    {
        return 3;
    }
    else if(mousey == starty + 4)
    {
        return 4;
    }
    else if(mousey == starty + 5)
    {
        return 5;
    }

    return -1;
}

int short_msg(WINDOW *chat_win,int sockfd,char *user)
{
    int i;
    int ch;
    int choice;
    MEVENT event; 
    WINDOW *msg_win;
    extern struct message msg;
    int startx = (COLS - 50)/2 + 2;
    int starty = (LINES - 24)/2 + 6;

    msg_win = subwin(stdscr,7,25,starty,startx);
    wbkgd(msg_win,COLOR_PAIR(2));
    box(msg_win,0,0);

    mvwprintw(msg_win,1,1,"欢迎来到趣谈聊天室");
    mvwprintw(msg_win,2,1,"好久不见");
    mvwprintw(msg_win,3,1,"我要下线了");
    mvwprintw(msg_win,4,1,"不好意思刚不在");
    mvwprintw(msg_win,5,1,"最近还好吗?");

    wrefresh(msg_win);
    
    while(1)
    {
        ch = wgetch(chat_win);

	switch(ch)
	{
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event))
		{
		    if(event.bstate && BUTTON1_CLICKED)
		    {
		        choice = report_choice_7(event.x,event.y);

			if(choice != -1)
			{
			    switch(choice)
			    {
			        case 1:
			        {
                                    strcpy(msg.msg,"欢迎来到趣谈聊天室");

				    break;
			        }
			        case 2:
			        {
                                    strcpy(msg.msg,"好久不见");
			            
				    break;
			        }
			        case 3:
			        {
                                    strcpy(msg.msg,"我要下线了");
			            
				    break;
			        } 
			        case 4:
			        {
                                    strcpy(msg.msg,"不好意思刚不在");
			            
				    break;
			        }
			        case 5:
			        {
                                    strcpy(msg.msg,"最近还好吗?");
			            
				    break;
			        }
				default:
				{
				    break;
				}
			    }
			    
			    delwin(msg_win);
                                    
		            for(i = 0; i < 7; i++)
			    {
			        mvwprintw(stdscr,starty + i,startx - 1,"                               ");
			    }
                                    
			    mvwhline(chat_win,15,1,'-',48);
                                   
			    refresh();

			    goto end;
			}
                        
		    }
		}
	    }
	}
    }

    end:
        private_chat(user,sockfd,0);
	return 0;
}
