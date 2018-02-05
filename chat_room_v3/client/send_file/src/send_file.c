#include <curses.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

int send_file(int sockfd,WINDOW *chat_win,char *user)
{
    FILE *fp;
    char file_name[10];
    char sql[MAX_SIZE];
    extern char now_user[10];
    extern struct message msg;
    
    strcpy(msg.name,now_user);
    strcpy(msg.toname,user);
    while(1)
    {
        echo();
        mvwprintw(chat_win,18,2,"请输入文件名:");
        mvwgetnstr(chat_win,18,15,file_name,10);
        wrefresh(chat_win);
        noecho();

	if(strlen(file_name) == 0)
	{
	    remind("文件名不能为空!");
	}
	else
	{
	    break;
	}
    }
    
    msg.action = SNF;

    msg.id = 1;

    write(sockfd,&msg,sizeof(struct message));
    
    sleep(1);
    
    mvwprintw(chat_win,18,2,"                                                ");
    wbkgd(chat_win,COLOR_PAIR(2));
    wrefresh(chat_win);

    if(msg.action == SNF_FAIL)
    {
	sprintf(sql,"用户%s不在线!",msg.toname);

        remind(sql);

	memset(sql,0,sizeof(sql));

	memset(&msg,0,sizeof(struct message));
    }
    else
    {
	fp = fopen(file_name,"a+");
        
	msg.id = 0;
            
	while(!feof(fp))
        {
	    msg.msg[1024] = 0;
	    strcpy(msg.name,now_user);
            strcpy(msg.toname,user);
	    strcpy(msg.users[0],file_name);
            
	    if(fgets(msg.msg,1024,fp) != NULL)
	    {
	        write(sockfd,&msg,sizeof(struct message));
	    }
            
        }

        msg.action = SNF_END;
        
	write(sockfd,&msg,sizeof(struct message));
    }

    return 0;
}
