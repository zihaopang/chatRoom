#include <curses.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int report_choice_8(int mousex,int mousey)
{
    int starty = LINES/3 - 10;
    int startx = (2 * COLS)/3 + 10;
    
    if(mousey == starty + 24 && mousex >= startx + 2 && mousex <= startx + 10)
    {
        return CHP;    
    }

    return -1;
}

int set(WINDOW *user_win,int sockfd)
{
    int ch;
    int choice;
    MEVENT event;
    WINDOW *set_win;
    int starty = LINES/3 - 10;
    int startx = (2 * COLS)/3 + 10;

    set_win = subwin(stdscr,3,10,starty + 23,startx + 2);
    
    wbkgd(set_win,COLOR_PAIR(2));
    mvwprintw(set_win,1,1,"修改密码");
    box(set_win,0,0);

    wrefresh(set_win);
    
    mousemask(ALL_MOUSE_EVENTS,NULL);
    keypad(user_win,TRUE);

    while(1)
    {
        ch = wgetch(user_win);

	switch(ch)
	{
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event))
		{
		    if(event.bstate && BUTTON1_CLICKED)
		    {
		        choice = report_choice_8(event.x,event.y);
                        
			if(choice != -1)
			{
			    switch(choice)
			    {
			        case CHP:
				{
				    change_passwd(sockfd);

				    goto end;

				    break;
				}
				default:
				{
				    break;
				}
			    }
			}
		    }
		}
	    }
	}
    }
    
    end:
        return 0;
}
