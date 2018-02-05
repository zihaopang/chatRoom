#include <stdlib.h> 
#include <termio.h>
#include <unistd.h>
#include <stdio.h> 
#include <errno.h> 
#include <string.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sqlite3.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int login_judge(sqlite3 *passwd_db,int new_fd)
{
    int nrow;
    int ncolumn;
    char *errmsg;
    char **result;
    char sql[1024];
    extern Link head;
    extern struct message msg;
    Link new_user = (Link)malloc(sizeof(Online));
    
    sprintf(sql,"select * from passwd where name='%s';",msg.name);
    sqlite3_get_table(passwd_db,sql,&result,&nrow,&ncolumn,&errmsg);
    
    memset(sql,0,sizeof(sql)); 
    
    if(nrow == 0)
    {
        msg.id = id_set();
        #if 0 
	for(i = 1;i <= nrow;i++)
	{
	    while(1)
	    {
	        if(*result[i * ncolumn + 0] == msg.id)
	        {
	            msg.id = id_set();
	        }
		else
		{
		    break;
		}
	    }

	    break;
	}
        #endif
	sprintf(sql,"insert into passwd(id,name,passwd) values(%d,'%s','%s');",msg.id,msg.name,msg.passwd);
	sqlite3_exec(passwd_db,sql,NULL,NULL,&errmsg);
        
        msg.action = LOGIN_SUCCESS;

	strcpy(new_user->name,msg.name);
	new_user->new_fd = new_fd;
	new_user->state = SAY;

	insert_new_user(&new_user,&head);
    }
    else
    {
        msg.action = LOGIN_FAIL;   
    }
    
    write(new_fd,&msg,sizeof(struct message));

    return 0;
}
