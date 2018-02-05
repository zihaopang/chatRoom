#include <stdio.h>
#include <string.h>

#include "/home/chat_room/include/all.h"

int private_chat(int sockfd)
{
    int i = 0;
    char ch = 'k';
    char infor[1024];
    char sh_msg[1024];
    extern char now_user[10];
    extern struct message msg;

    system("reset");
    
    printf("/----------------私聊界面----------------/\n");

    while((ch != 'q') && (ch != 'r'))
    {
        msg.action = STO;
	
        printf("请输入用户名:");
        scanf("%s",msg.toname);

        printf("请输入发送内容:");
	getchar();
        
        scanf("%[^\n]",infor);

	short_msg(infor,sh_msg);

	strcpy(msg.msg,sh_msg);

        strcpy(msg.name,now_user);

        write(sockfd,&msg,sizeof(struct message));
	
	printf("输入'q'键返回主界面，'r'键清空聊天窗口，任意键继续\n");

	getchar();
	ch = getchar();
    }
    
    if(ch == 'q')
    {
        system("reset");

	welcome_table();

	input_order(sockfd);
    }
    else if(ch == 'r')
    {
        system("reset");
	
	private_chat(sockfd);
    }

    return 0;
}
