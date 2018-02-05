#include "/home/chat_room/include/all.h"

int insert_new_user(Link *new_user,Link *head)
{
    (*new_user)->next = *head;
    *head = *new_user;

    return 0;
}
