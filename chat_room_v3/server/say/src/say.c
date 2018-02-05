#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

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
