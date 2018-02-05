#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

int remind(char *remind)
{
    setlocale(LC_ALL,"");
    
    WINDOW *remind_win;
     
    remind_win = newwin(5,+ 40,(LINES - 5)/2,(COLS - 40)/2);
    wbkgd(remind_win,COLOR_PAIR(2));
    wrefresh(remind_win);
    mvwprintw(remind_win,2,(40 - strlen(remind))/2,"%s",remind);
    wrefresh(remind_win);
    sleep(2);
    
    delwin(remind_win);
    touchwin(stdscr);
    refresh();
    
    return 0;
}
