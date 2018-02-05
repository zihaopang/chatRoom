#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
#include <string.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sqlite3.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int log_judge(sqlite3 *passwd_db,int new_fd)
{
    int nrow;
    int ncolumn;
    int flag = 0;
    char *errmsg;
    char **result;
    extern Link head;
    Link temp = head;
    char sql[MAX_SIZE * 10];
    extern struct message msg;
    Link new_user = (Link)malloc(sizeof(Online));

    sprintf(sql,"select * from passwd where name='%s' or id=%d",msg.name,msg.id);
    
    sqlite3_get_table(passwd_db,sql,&result,&nrow,&ncolumn,&errmsg);
    
    if(nrow == 0)
    {
        msg.action = LOG_FAIL;
        
	if(!strcmp(msg.name,"admin"))
	{
	    strcpy(msg.msg,"尚未初始化");
	}
	else
	{
	    msg.action = LOG_FAIL;
	    strcpy(msg.msg,"尚未注册");
	}

    }
    else
    {
	strcpy(msg.name,result[ncolumn + 1]);
    
        while(temp != NULL)
        {
            if(!strcmp(msg.name,temp->name))
	    {
                flag = 1;
	        break;
	    }

	    temp = temp->next;
        }
        
	if(((flag == 0) && ((strcmp(result[ncolumn + 2],msg.passwd) == 0))) || ((flag == 0) && (*result[ncolumn + 0] == msg.id)))
        {
            msg.action = LOG_SUCCESS;
        
	    strcpy(new_user->name,msg.name);
	    new_user->new_fd = new_fd;
	    new_user->state = SAY;

	    insert_new_user(&new_user,&head);
        }
        else if(flag == 1)
        {
            msg.action = LOG_FAIL;

	    strcpy(msg.msg,"已在线");
        }
        else
        {
            msg.action = LOG_FAIL;
	
	    strcpy(msg.msg,"密码错误");
        }
    
    }
    
    write(new_fd,&msg,sizeof(struct message));
    
    flag = 0;

    return 0;
}    

