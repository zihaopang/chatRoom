#include <locale.h>
#include <string.h>
#include <stdlib.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

Content tables;

int report_choice_4(int mousex,int mousey,int num)
{
    int starty = LINES/3 -2;
    int startx = (2 * COLS)/3 + 13;


    if(mousey == starty && mousex >= startx && mousex <= startx + 8)
    {
	return SURE;
    }
    else if(mousey == starty + 18 && mousex >= startx - 2 && mousex <= startx + 2)
    {
        return SET; 
    }
    else if(mousey > starty && mousey <= starty + num && mousex >= startx && mousex <= startx + 8)
    {
        return (mousey - starty);
    }
    else if(mousey == starty - 7 && mousex == startx + 20)
    {
        return EXIT;
    }
    
    return -1;
}

int user_table(int sockfd)
{
    int ch;
    int choice;
    int num = 0;
    MEVENT event;
    WINDOW *user_win;
    int show_flag = 1;
    extern char now_user[10];
    setlocale(LC_ALL,"");
    char users[MAX_SIZE][10];
    int starty = LINES/3 - 10;
    int startx = (2 * COLS)/3 + 10;

    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_CYAN);

    bkgd(COLOR_PAIR(1));
    refresh();

    user_win = subwin(stdscr,28,25,starty,startx);
    keypad(user_win,TRUE);
    
    mvwhline(user_win,2,2,'-',21);
    mvwaddch(user_win,2,1,'+');
    mvwvline(user_win,3,1,'|',23);
    mvwaddch(user_win,25,1,'+');
    mvwhline(user_win,25,2,'-',22);
    mvwaddch(user_win,25,23,'+');
    mvwvline(user_win,3,23,'|',22);
    mvwaddch(user_win,2,23,'+');
    mvwhline(user_win,7,2,'-',21);

    wbkgd(user_win,COLOR_PAIR(2));
    wattron(user_win,A_REVERSE);
    mvwaddstr(user_win,1,2,"趣谈");
    wattroff(user_win,A_REVERSE);
    mvwaddch(user_win,1,23,'x');
    mvwaddstr(user_win,3,3,(char *)now_user);
    mvwaddstr(user_win,26,1,"=设置");
    mvwaddstr(user_win,8,3,">在线好友");
    
    mousemask(ALL_MOUSE_EVENTS,NULL);
    wrefresh(user_win);
    
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
                        choice = report_choice_4(event.x,event.y,num);

			if(choice != -1)
			{
                            if(SURE == choice)
			    {
			        if(1 == show_flag)
			        {
			            draw_menu(sockfd,user_win,&num,users);

				    users[MAX_SIZE][10] = 0;
                                    
				    show_flag = 0;
			        }
				else if(0 == show_flag)
				{
				    clear();
				    refresh();
				    user_table(sockfd);
				    show_flag = 1;
				}
			    }
			    else if(SET == choice)
			    {
			        set(user_win,sockfd);
			    }
			    else if(EXIT == choice)
			    {
			        endwin();
				exit(1);
			    }
			    else
			    {
				strcpy(tables.name,users[choice - 1]);
				tables.num = 0;

				chat_table(user_win,users[choice - 1],sockfd);   
			    }
			}
		    }
		}

		break;
	    }
	}
    }
    
    return 0;
}
