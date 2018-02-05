#include <stdio.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int check_state(int new_fd)
{
    extern Link head;
    Link temp = head;

    while(temp != NULL)
    {
        if(temp->new_fd == new_fd)
	{
	    break;
	}

	temp = temp->next;
    }

    return temp->state;
}
