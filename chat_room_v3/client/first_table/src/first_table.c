#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

#define ENTER_1 10
char *choices[] =
{
    "登录",
    "注册"
};
    
int choice_num = sizeof(choices)/sizeof(choices[0]);

int report_choice(int mousey,int mousex)
{
    int choice;
    int k = (LINES - 15)/2 + 10;
    int j = (COLS - 30)/2 + 6;
    
    for(choice = 0; choice < choice_num; choice++)
    {
        if(mousey == k && mousex >= j && mousex <= j + 3)
	{
	    return LOG;
	}
	else if(mousey == k && mousex >= j + 12 && mousex <= j + 12 + 3)
	{
	    return LOGIN;
	}
	else
	{
	    continue;
	}
    }

    return -1;
}

int first_table(sockfd)
{
    int c;
    int record;
    MEVENT event;

    WINDOW *first_win; 

    setlocale(LC_ALL,"");

    initscr();
    clear();
    noecho();
    cbreak();
    start_color();
    
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    bkgd(COLOR_PAIR(1));
    refresh();

    init_pair(2,COLOR_BLACK,COLOR_CYAN);
    
    first_win = newwin(15,30,(LINES - 15)/2,(COLS - 30)/2);
    wbkgd(first_win,COLOR_PAIR(2));
    box(first_win,0,0);
    keypad(first_win,TRUE);
    
    mvwprintw(first_win,5,6,"欢迎来到趣谈聊天！");
    
    wattron(first_win,A_REVERSE);
    mvwprintw(first_win,10,6,"登录");
    mvwprintw(first_win,10,18,"注册");
    wattroff(first_win,A_REVERSE);
    wmove(first_win,0,0);
    wrefresh(first_win);

    mousemask(ALL_MOUSE_EVENTS,NULL);
    
    while(1)
    {
        c = wgetch(first_win);
	
	switch(c)
	{
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event))
		{
		    if(event.bstate && BUTTON1_CLICKED)
		    {
		        record = report_choice(event.y,event.x);

			if(record != -1)
			{
			    if(record == LOG)
			    {
                                delwin(first_win);
	                        refresh();
				
				log_table(sockfd);
				
				goto end;
			    }
			    else
			    {
                                delwin(first_win);
                                refresh();

				reg_table(sockfd);
				
				goto end;
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
    return 0;
}
