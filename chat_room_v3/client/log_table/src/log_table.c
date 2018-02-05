#include <locale.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

struct message msg;

int report_choice_2(mousex,mousey)
{
    int y = (LINES - 15)/2 + 6;
    int x = (COLS - 40)/2 + 13;

    if(mousey == y && mousex >= x && mousex <= x + 20)
    {
        return BLANK_1;
    }
    else if(mousey == y + 3 && mousex >= x && mousex <= x + 20)
    {
        return BLANK_2;
    }
    else if(mousey == y + 6 && mousex >= x + 5 && mousex <= x + 8)
    {
        return SURE;
    }
    else
    {
        return -1;
    }
}

int log_table(int sockfd)
{
    int c;
    char ch;
    int j= 0;
    int choice;
    int i = 13;
    MEVENT event;
    msg.action = LOG;
    int name_flag = 0;
    int sure_flag = 0;
    int passwd_flag = 0;
    char input[MAX_SIZE];

    setlocale(LC_ALL,"");
    
    WINDOW *passwd_win;
    
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();
    mousemask(ALL_MOUSE_EVENTS,NULL);
        
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    bkgd(COLOR_PAIR(1));
    refresh();

    init_pair(2,COLOR_BLACK,COLOR_CYAN);

    passwd_win = newwin(15,40,(LINES - 15)/2,(COLS - 40)/2);
    wbkgd(passwd_win,COLOR_PAIR(2));
    box(passwd_win,0,0);
    keypad(passwd_win,TRUE);
    mvwprintw(passwd_win,3,14,"趣谈登录窗口");
    mvwprintw(passwd_win,6,8,"用户:");
    mvwprintw(passwd_win,9,8,"密码:");
    
    wbkgdset(passwd_win,COLOR_PAIR(1));
    mvwprintw(passwd_win,6,13,"                    ");
    mvwprintw(passwd_win,9,13,"                    ");
    
    wbkgdset(passwd_win,COLOR_PAIR(2));
    mvwprintw(passwd_win,12,18,"登录");
    wmove(passwd_win,0,0);
    
    refresh();
    
    while(1)
    {
        c = wgetch(passwd_win);
	
	switch(c)
	{
	    
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event)) 
	        {
		    if(event.bstate && BUTTON1_CLICKED)
		    {
			choice = report_choice_2(event.x,event.y);
		        
			if(choice != -1)
		        {
		            switch(choice)
			    {
			        case BLANK_1:
			        {
				    echo();

				    wrefresh(passwd_win);
				    mvwgetnstr(passwd_win,6,13,input,20);

				    if((input[0] >= '1') && (input[0] <= '9'))
				    {
				        msg.id = atoi(input);
				    }
				    else
				    {
				        strcpy(msg.name,input);
				    }

				    memset(input,0,sizeof(input));
                                    
				    name_flag = 1;
                                     
				    break;
			        }
			        case BLANK_2:
			        {
                                    noecho();
				    mousemask(0,NULL);
				    refresh();
                                    
				    while((ch = mvwgetch(passwd_win,9,i)) != '\n')
				    {
			                noecho();
				        wrefresh(passwd_win);
					msg.passwd[j] = ch;
					i++;
					j++;
                                        
					echo();
					mvwaddch(passwd_win,9,i-1,'*');
					wrefresh(passwd_win);
                                        
					if(j == 10)
					{
					    break;
					}
				    }
                                    
				    msg.passwd[j] = '\0';
                                    
				    i = 13;
				    j = 0;
				    passwd_flag = 1;
                                    
				    mousemask(ALL_MOUSE_EVENTS,NULL);
				    refresh();

				    break;
			        }
			        case SURE:
			        {
			            sure_flag = 1;

				    break;
			        }
			        default:
			        {
			            break;
			        }
			    }

			    if((passwd_flag == 1 && name_flag == 1) || sure_flag == 1)
			    {
			        goto prac;
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

	refresh();
    }

prac:
    while(msg.action == LOG)
    {
        write(sockfd,&msg,sizeof(struct message)); 
        
	read(sockfd,&msg,sizeof(struct message)); 
    }
    
    delwin(passwd_win);
    
    refresh();
    
    return 0;
}
