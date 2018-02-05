#include <stdio.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int del_user(int new_fd)
{
    extern Link head;

    if(head == NULL)
    {
        return -1;
    }
    
    Link temp = head;

    if(head->new_fd == new_fd)
    {
        head = head->next;
    }
    else
    {
        Link ptr = temp;

        temp = temp->next;

	while(temp != NULL)
	{
	    if(temp->new_fd == new_fd)
	    {
	        ptr->next = temp->next;
	    }

	    ptr = temp;
	    temp = temp->next;
	}
    }

    return 0;

}
