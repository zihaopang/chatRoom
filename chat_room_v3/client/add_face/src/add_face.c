#include <curses.h>
#include <locale.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int report_choice_6(int mousex,int mousey)
{
    int startx = (COLS - 50)/2 - 1;
    int starty = (LINES - 24)/2 + 6;
    
    if(mousey == starty + 1)
    {
        if(mousex >= startx + 1 && mousex <= startx + 1 + strlen("^_^"))
	{
	    return 1;
	}
        else if(mousex >= startx + 5 && mousex <= startx + 5 + strlen("-_-#"))
	{
	    return 2;
	}
        else if(mousex >= startx + 10 && mousex <= startx + 10 + strlen("=_="))
	{
	    return 3;
	}
        else if(mousex >= startx + 15 && mousex <= startx + 15 + strlen("^o^"))
	{
	    return 4;
	}
    }
    else if(mousey == starty + 3)
    {
        if(mousex >= startx + 1 && mousex <= startx + 1 + strlen(":-)"))
	{
	    return 5;
	}
        else if(mousex >= startx + 5 && mousex <= startx + 5 + strlen(":-D"))
	{
	    return 6;
	}
        else if(mousex >= startx + 10 && mousex <= startx + 10 + strlen(";-("))
	{
	    return 7;
	}
        else if(mousex >= startx + 15 && mousex <= startx + 15 + strlen(":D"))
	{
	    return 8;
	}
            
    }
    else if(mousey == starty + 5)
    {
        if(mousex >= startx + 1 && mousex <= startx + 1 + strlen("O_o"))
	{
	    return 9;
	}
        else if(mousex >= startx + 5 && mousex <= startx + 5 + strlen("OvO"))
	{
	    return 10;
	}
        else if(mousex >= startx + 10 && mousex <= startx + 10 + strlen("i_i"))
	{
	    return 11;
	}
        else if(mousex >= startx + 15 && mousex <= startx + 15 + strlen("T_T"))
	{
	    return 12;
	}
    }

    return -1;
}

int add_face(WINDOW *chat_win,int sockfd,char *user)
{
    WINDOW *face_list;

    int i;
    int ch;
    int choice;
    MEVENT event; 
    extern struct message msg;
    int startx = (COLS - 50)/2 - 1;
    int starty = (LINES - 24)/2 + 6;

    face_list = subwin(stdscr,7,20,starty,startx);

    box(face_list,0,0);

    mvwprintw(face_list,1,1,"^_^");
    mvwprintw(face_list,1,5,"-_-#");
    mvwprintw(face_list,1,10,"=_=");
    mvwprintw(face_list,1,15,"^o^");
    mvwprintw(face_list,3,1,":-)");
    mvwprintw(face_list,3,5,":-D");
    mvwprintw(face_list,3,10,";-(");
    mvwprintw(face_list,3,15,":D");
    mvwprintw(face_list,5,1,"O_o");
    mvwprintw(face_list,5,5,"OvO");
    mvwprintw(face_list,5,10,"i_i");
    mvwprintw(face_list,5,15,"T.T");
    wmove(chat_win,0,0);

    wbkgd(face_list,COLOR_PAIR(2));
    wrefresh(face_list);
    
    mousemask(ALL_MOUSE_EVENTS,NULL);
    keypad(chat_win,TRUE);
    wrefresh(chat_win);
   
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
		        choice = report_choice_6(event.x,event.y);

			if(choice != -1)
			{
			    switch(choice)
			    {
			        case 1:
			        {
				    strcpy(msg.msg,"^_^");

				    break;
			        }
			        case 2:
			        {
				    strcpy(msg.msg,"-_-#");
			            break;
			        }
			        case 3:
			        {
				    strcpy(msg.msg,"=_=");
			            break;
			        }
			        case 4:
			        {
				    strcpy(msg.msg,"^o^");
			            break;
			        }
			        case 5:
			        {
				    strcpy(msg.msg,":-)");
			            break;
			        }
			        case 6:
			        {
				    strcpy(msg.msg,":-D");
			            break;
			        }
			        case 7:
			        {
				    strcpy(msg.msg,";-(");
			            break;
			        }
			        case 8:
			        {
				    strcpy(msg.msg,":D");
			            break;
			        }
			        case 9:
			        {
			 	    strcpy(msg.msg,"O_o");
			            break;
			        }
			        case 10:
			        {
				    strcpy(msg.msg,"OvO");
			            break;
			        }
			        case 11:
			        {
			 	    strcpy(msg.msg,"i_i");
			            break;
			        }
			        case 12:
			        {
				    strcpy(msg.msg,"T.T");
			            break;
			        }
			        default:
				{
			            break;
	                 	}
			    }
			            
			    delwin(face_list);
                                    
			    for(i = 0; i < 7; i++)
			    {
				mvwprintw(stdscr,starty + i,startx - 1,"                         ");
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
