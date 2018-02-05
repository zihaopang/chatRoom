#include <stdio.h>
#include <string.h>

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int private_chat(int new_fd)
{
    int state;
    int flag = 0;
    extern Link head;
    int recorder = new_fd;
    extern struct message msg;

    Link temp = head;

    state = check_state(new_fd);

    while(temp != NULL)
    {
        if(!strcmp(temp->name,msg.toname))
	{
	    new_fd = temp->new_fd;
	    
	    flag = 1;

	    break;
	}

	temp=temp->next;
    }
    
    if(state == SAY)
    {
        if(flag != 0)
        {
            msg.action = STO_SUCCESS;
        }
        else
        {
            msg.action = STO_FAIL;

	    strcpy(msg.name,msg.toname);
        }
    
        write(new_fd,&msg,sizeof(struct message));
    }
    else
    {
        msg.action = NO_SAY;
        
	write(recorder,&msg,sizeof(struct message));
    }

    return 0;
}
