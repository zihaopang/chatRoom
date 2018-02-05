#include <stdio.h>

#include "/home/chat_room/include/all.h"

int say(int new_fd)
{
    extern Link head;
    extern struct message msg;

    Link temp = head;

    while(temp != NULL)
    {
        if(!strcmp(temp->name,msg.name))
	{
	    temp->state = SAY;

	    break;
	}

	temp =temp->next;
    }

    msg.action = SAY;

    temp = head;

    while(temp != NULL)
    {
        if(!strcmp(temp->name,msg.name))
	{
	    new_fd = temp->new_fd;

	    break;
	}

	temp = temp->next;
    }

    write(new_fd,&msg,sizeof(struct message));
    
    return 0;
}
