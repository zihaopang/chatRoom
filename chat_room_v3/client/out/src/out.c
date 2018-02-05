#include <curses.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int out(WINDOW *win,int sockfd)
{
    int i;
    extern struct message msg;
    
    msg.action = OUT;

    for(i = 5 ; i <= 12; i++)
    {
        mvwprintw(win,i,10,"                             ");
    }

    wrefresh(win);
    
    mvwprintw(win,6,13,"需被踢出的用户:");
    wrefresh(win);

    wbkgdset(win,COLOR_PAIR(1));
    mvwprintw(win,9,13,"                    ");
    wbkgdset(win,COLOR_PAIR(2));
    wrefresh(win);
    
    echo();
    mvwgetnstr(win,9,13,msg.name,20);
    noecho();

    write(sockfd,&msg,sizeof(struct message));

    msg.action = 0;
    memset(msg.name,0,sizeof(msg.name));

    remind("已操作");

    return 0;
}
