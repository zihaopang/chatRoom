#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int out()
{
    int del_fd = 0;
    extern Link head; 
    extern struct message msg;
    
    Link temp = head;

    while(temp != NULL)
    {
        if(!strcmp(msg.name,temp->name))
	{
	    del_fd = temp->new_fd;

	    break;
	}

	temp = temp->next;
    }

    del_user(del_fd);

    write(del_fd,&msg,sizeof(struct message));
    
    return 0;
}
