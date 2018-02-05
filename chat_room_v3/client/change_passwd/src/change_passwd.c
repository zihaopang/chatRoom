#include <locale.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int report_choice_9(mousex,mousey)
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

int change_passwd(int sockfd)
{
    int c;
    char ch;
    int j= 0;
    int choice;
    int i = 13;
    MEVENT event;
    int passwd1_flag = 0;
    int sure_flag = 0;
    int passwd2_flag = 0;
    extern char now_user[10];
    extern struct message msg;
    
    msg.action = CHP;
    strcpy(msg.name,(char *)now_user);

    setlocale(LC_ALL,"");
    
    WINDOW *chp_win;
    
    mousemask(ALL_MOUSE_EVENTS,NULL);
        
    chp_win = subwin(stdscr,15,40,(LINES - 15)/2,(COLS - 40)/2);
    wbkgd(chp_win,COLOR_PAIR(2));
    box(chp_win,0,0);
    keypad(chp_win,TRUE);
    mvwprintw(chp_win,3,15,"修改密码");
    mvwprintw(chp_win,6,5,"原密码:");
    mvwprintw(chp_win,9,5,"新密码:");
    
    wbkgdset(chp_win,COLOR_PAIR(1));
    mvwprintw(chp_win,6,13,"                    ");
    mvwprintw(chp_win,9,13,"                    ");
    
    wbkgdset(chp_win,COLOR_PAIR(2));
    mvwprintw(chp_win,12,18,"确认");
    wmove(chp_win,0,0);
    
    wrefresh(chp_win);
    
    memset(msg.passwd,0,sizeof(msg.passwd));
    
    while(1)
    {
        c = wgetch(chp_win);
	
	switch(c)
	{
	    case KEY_MOUSE:
	    {
	        if(OK == getmouse(&event)) 
	        {
		    if(event.bstate && BUTTON1_CLICKED)
		    {
			choice = report_choice_9(event.x,event.y);
		        
			if(choice != -1)
		        {
		            switch(choice)
			    {
			        case BLANK_1:
			        {
                                    mousemask(0,NULL);
                                    noecho();
				    refresh();
                                    
				    while((ch = mvwgetch(chp_win,6,i)) != '\n')
				    {
			                noecho();
				        
					wrefresh(chp_win);
					msg.passwd[j] = ch;
					i++;
					j++;
                                        
					echo();
					mvwaddch(chp_win,6,i-1,'*');
					wrefresh(chp_win);
                                        
					if(j == 10)
					{
					    break;
					}

				    }
                                    
				    msg.passwd[j] = '\0';
                                    
				    i = 13;
				    j = 0;
				    passwd1_flag = 1;
				    
				    mousemask(ALL_MOUSE_EVENTS,NULL);
				    refresh();

				    break;
			            
				}
			        case BLANK_2:
			        {
                                    mousemask(0,NULL);
                                    noecho(); 
				    refresh();
				    
				    while((ch = mvwgetch(chp_win,9,i)) != '\n')
				    {

			                noecho();
				        wrefresh(chp_win);
					msg.msg[j] = ch;
					i++;
					j++;
                                        
					echo();
					mvwaddch(chp_win,9,i-1,'*');
					wrefresh(chp_win);
                                        
					if(j == 10)
					{
					    break;
					}
				    }
                                    
				    msg.msg[j] = '\0';
                                    
				    i = 13;
				    j = 0;
				    passwd2_flag = 1;
				    
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

			    if((passwd1_flag == 1 && passwd2_flag == 1) || sure_flag == 1)
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
    write(sockfd,&msg,sizeof(struct message)); 
    
    sleep(1);

    memset(&msg,0,sizeof(struct message));

    delwin(chp_win);
    
    clear();
    
    user_table(sockfd);

    refresh();
    
    return 0;
}
