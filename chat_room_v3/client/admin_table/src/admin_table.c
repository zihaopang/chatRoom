#include <curses.h>
#include <locale.h>
#include <stdlib.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int report_choice_10(int mousex,int mousey)
{
    int startx = COLS/2 - 20;
    int starty = LINES/2 - 7;

    if(mousey == starty + 5 && mousex >= startx + 4 && mousex <= startx + 10)
    {
        return NO_SAY;
    }
    else if(mousey == starty + 7 && mousex >= startx + 4 && mousex <= startx + 10)
    {
        return SAY;
    }
    else if(mousey == starty + 9 && mousex >= startx + 4 && mousex <= startx + 10)
    {
        return OUT;
    }
    else if(mousey == starty + 10 && mousex >= startx + 4 && mousex <= startx + 10)
    {
        return EXIT;
    }

    return -1;
}

int admin_table(int sockfd)
{
    initscr();
    noecho();
    cbreak();
    start_color();
    
    setlocale(LC_ALL,"");
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_CYAN);

    int ch;
    int choice;
    MEVENT event;
    WINDOW *admin_win;
    int startx = COLS/2 - 20;
    int starty = LINES/2 - 7;
    
    admin_win = subwin(stdscr,14,40,starty,startx);
    
    box(admin_win,0,0);
    bkgd(COLOR_PAIR(1));
    wbkgd(admin_win,COLOR_PAIR(2));
    refresh();
    
    mvwprintw(admin_win,2,15,"管理员界面");
    wattron(admin_win,A_REVERSE);
    mvwprintw(admin_win,5,4,"禁言");
    mvwprintw(admin_win,7,4,"解禁");
    mvwprintw(admin_win,9,4,"踢人");
    mvwprintw(admin_win,11,4,"退出");
    wattroff(admin_win,A_REVERSE);
    wmove(admin_win,0,0);
    wrefresh(admin_win);
    
    keypad(admin_win,TRUE);
    mousemask(ALL_MOUSE_EVENTS,NULL);
    refresh();

    while(1)
    {
        ch = wgetch(admin_win);

	switch(ch)
	{
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event))
		{
		    if(event.bstate && BUTTON1_CLICKED)
		    {
		        choice = report_choice_10(event.x,event.y); 

			if(choice != -1)
			{
			    switch(choice)
			    {
			        case NO_SAY: 
			        {
			            no_say(admin_win,sockfd);

				    break;
			        }
			        case SAY: 
			        {
			            say(admin_win,sockfd);
			            break;
			        }
			        case OUT: 
			        {
			            out(admin_win,sockfd);
			            break;
			        }
			        case EXIT: 
			        {
			            endwin();
                                    exit(1);

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

    return 0;
}

