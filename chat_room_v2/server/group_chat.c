#include <stdio.h>

#include "/home/chat_room/include/all.h"

int group_chat(int new_fd)
{
    int state;
    extern Link head;
    Link temp = head;
    int recorder = new_fd;
    extern struct message msg;
    
    msg.action = STA;

    state = check_state(new_fd);
    
    if(state == SAY)
    {
        while(temp != NULL)
        {
	    new_fd = temp->new_fd;
        
	    msg.action = STA_SUCCESS;

	    write(new_fd,&msg,sizeof(struct message));
       	
	    temp = temp->next;
	}
    }
    else
    {
        msg.action = NO_SAY;
	
	write(new_fd,&msg,sizeof(struct message));
    }
    
    return 0;
}
