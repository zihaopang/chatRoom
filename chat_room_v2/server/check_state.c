#include <stdio.h>

#include "/home/chat_room/include/all.h"

int check_state(int new_fd)
{
    extern Link head;
    Link temp = head;
    extern struct message msg;

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
