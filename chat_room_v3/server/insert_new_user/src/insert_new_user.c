#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/server/declear.h"

int insert_new_user(Link *new_user,Link *head)
{
    (*new_user)->next = *head;
    *head = *new_user;

    return 0;
}
