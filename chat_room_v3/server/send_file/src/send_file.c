#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

void send_file(int new_fd)
{
    int to_fd;
    int flag = 0;
    extern Link head;
    extern struct message msg;
    
    Link temp = head;

    while(temp != NULL)
    {
        if(strcmp(msg.toname,temp->name) == 0)
	{
	    to_fd = temp->new_fd;

	    flag = 1;
            
	    break;
	}

	temp = temp->next;
    }
    
    if(flag == 1)
    {
	if(msg.id != 1)
	{
            while(msg.action == SNF)
	    {
	        write(to_fd,&msg,sizeof(struct message));
	        
		*msg.msg = 0;
		msg.action = 0;

	        read(new_fd,&msg,sizeof(struct message));
	    }

	    write(to_fd,&msg,sizeof(struct message));
               
	    msg.action = SNF_SUCCESS;
	   
	    write(new_fd,&msg,sizeof(struct message));
	}
    }
    else
    {
        msg.action = SNF_FAIL;
	
	write(new_fd,&msg,sizeof(struct message));
    }

}
