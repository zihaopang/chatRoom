#include <stdio.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

int group_chat(int sockfd)
{
    int i;
    int k;
    char ch;
    char infor[1024];
    char sh_msg[1024];
    extern char now_user[10];
    extern struct message msg;
    
    system("reset");
    
    printf("/----------------群发窗口----------------/\n");
    printf("'q'键返回，'r'键清空，任意键继续\n");

    while((ch != 'q') && (ch != 'r'))
    {
        msg.action = STA;
	
        printf("请输入发送内容:");
        
        scanf("%[^\n]",infor);

	short_msg(infor,sh_msg);
	
	strcpy(msg.msg,sh_msg);

        strcpy(msg.name,now_user);

        write(sockfd,&msg,sizeof(struct message));
        
	memset(infor,0,sizeof(infor));
        
	
	getchar();	

	ch = getchar();

    }
    
    if(ch == 'q')
    {
        system("reset");

	welcome_table();

	getchar();

	input_order(sockfd);
    }
    else if(ch == 'r')
    {
        system("reset");
	
	group_chat(sockfd);
    }
    
    admin_reset();

    return 0;
}
