#include <stdio.h>

#include "/home/chat_room/include/all.h"

int out()
{
    int del_fd;
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

}
