#include <locale.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int report_choice_5(int mousex,int mousey)
{
    int start_line = (LINES - 24)/2 + 13;
    int start_col = (COLS - 50)/2 - 7;

    if(mousey == start_line && mousex >= start_col && mousex <= start_col + 3)
    {
        return CHAT;
    }
    else if(mousey == start_line && mousex >= start_col + 7 && mousex <= start_col + 10)
    {
        return FACE;
    }
    else if(mousey == start_line && mousex >= start_col + 14 && mousex <= start_col + 17)
    {
        return MSG;
    }
    else if(mousey == start_line && mousex >= start_col + 21 && mousex <= start_col + 24)
    {
        return FLE;
    }
    else if(mousey == start_line && mousex >= start_col + 28 && mousex <= start_col + 31)
    {
        return STA;
    }
    else if(mousey == start_line + 7 && mousex >= start_col + 29 && mousex <= start_col + 34)
    {
        return SEND;
    }
    else if(mousey == start_line +7 && mousex >= start_col + 37 && mousex <= start_col + 42)
    {
        return EXIT;
    }

    return -1;
}

int chat_table(WINDOW *user_win,char *user,int sockfd)
{
    setlocale(LC_ALL,"");
    
    int ch;
    int choice;
    MEVENT event;
    extern Content tables;
    
    tables.chat_win = subwin(stdscr,25,50,(LINES - 24)/2 - 3,(COLS - 50)/2 - 10);
    wbkgd(user_win,COLOR_PAIR(2));
    wrefresh(user_win);
    wbkgd(tables.chat_win,COLOR_PAIR(2));
    wrefresh(tables.chat_win);
    
    box(tables.chat_win,'|','-');
    
    mvwhline(tables.chat_win,5,1,'-',48);
    mvwhline(tables.chat_win,15,1,'-',48);
    mvwhline(tables.chat_win,17,1,'-',48);
    
    mvwaddstr(tables.chat_win,1,2,user);
    mvwaddstr(tables.chat_win,16,3,"聊天");
    mvwaddstr(tables.chat_win,16,10,"表情");
    mvwaddstr(tables.chat_win,16,17,"短语");
    mvwaddstr(tables.chat_win,16,24,"文件");
    mvwaddstr(tables.chat_win,16,31,"群发");
    mvwaddstr(tables.chat_win,23,32,"|发送|");
    mvwaddstr(tables.chat_win,23,40,"|关闭|");
    wmove(tables.chat_win,0,0);
    wrefresh(tables.chat_win);
    
    keypad(tables.chat_win,TRUE);
    
    mousemask(ALL_MOUSE_EVENTS,NULL);

    while(ch)
    {
        ch = wgetch(tables.chat_win);
	
	switch(ch)
	{
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event))
		{
		    if(event.bstate && BUTTON1_CLICKED)
		    {
		        choice = report_choice_5(event.x,event.y);

			switch(choice)
			{
			    case CHAT:
			    {
				private_chat(user,sockfd,1);

				break;
			    }
			    case FACE:
			    {
			        add_face(tables.chat_win,sockfd,user);

				break;
			    }
			    case MSG:
			    {
			        short_msg(tables.chat_win,sockfd,user);

				break;
			    }
			    case FLE:
			    {
                                send_file(sockfd,tables.chat_win,user);

				break;
			    }
			    case STA:
			    {
				private_chat(user,sockfd,2);
			    }
			    case SEND:
			    {
				break;
			    }
			    case EXIT:
			    {
				clear();
				
				refresh();
				
				goto end;
			    }
			    default:
			    {
			        break;
			    }
			}
		    }
		}

		break;
	    }
	    default:
	    {
	        break;
	    }
	}

    }

    end:
	delwin(tables.chat_win);
	tables.num = 0;
	*tables.name = 0;
	user_table(sockfd);
	return 0;

}
