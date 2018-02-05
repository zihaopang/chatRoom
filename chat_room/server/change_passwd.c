#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "/home/chat_room/include/all.h"

int change_passwd(int new_fd,sqlite3 *passwd_db)
{
    int nrow;
    int ncloumn;
    char *errmsg;
    char **result;
    char sql[1024];
    char user_name[10];
    
    extern Link head;
    extern struct message msg;

    Link temp = head;

    while(temp != NULL)
    {
        if(new_fd == temp->new_fd)
	{
	    strcpy(user_name,temp->name);

	    break;
	}

	temp = temp->next;
    }
    
    sprintf(sql,"select * from passwd where name='%s';",msg.name);

    sqlite3_get_table(passwd_db,sql,&result,&nrow,&ncloumn,&errmsg);

    memset(sql,0,sizeof(sql));
    
    if(strcmp(result[ncloumn + 2],msg.passwd) == 0)
    {
	sprintf(sql,"update passwd set passwd='%s' where name='%s';",msg.msg,user_name);

        sqlite3_exec(passwd_db,sql,NULL,NULL,&errmsg);

	msg.action = CHP_SUCCESS;
    }
    else
    {
        msg.action = CHP_FAIL;
    }

    write(new_fd,&msg,sizeof(struct message));

}
