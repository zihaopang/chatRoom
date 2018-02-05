#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int no_say()
{
    extern Link head;
    Link temp = head;
    extern struct message msg;

    while(temp != NULL)
    {
        if(!strcmp(temp->name,msg.name))
	{
	    temp->state = NO_SAY;
	    break;
	}

	temp = temp->next;
    }
    
    return 0;
}
