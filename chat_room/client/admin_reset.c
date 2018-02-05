#include <stdio.h>

#include "/home/chat_room/include/all.h"

void admin_reset(int sockfd)
{
   char ch;
   
   while(1)
   {

       printf("\033[1;34m输入任意键返回\033[0m");
       
       getchar();
       ch = getchar();
       
       system("reset");

       admin_table();
   
       admin_cmd(sockfd);
   }
 
}
