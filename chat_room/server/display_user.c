#include <stdio.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

int display_user(int new_fd)
{
    int i = 0;
    extern Link head;
    extern struct message msg;
    
    Link temp = head;
    
    while(temp != NULL)
    {
	strcpy(msg.users[i],temp->name);
	
	i++;
	
	temp = temp->next;
    }
    
    msg.action = DIS_SUCCESS;
    
    write(new_fd,&msg,sizeof(struct message));

    return 0;
}
