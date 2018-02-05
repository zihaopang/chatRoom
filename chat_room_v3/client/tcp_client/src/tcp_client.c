#include <stdio.h>
#include <errno.h> 
#include <netdb.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <netinet/in.h> 

#include "/home/chat_room_v3/include/all.h"
#include "/home/chat_room_v3/client/declear.h"

struct message msg;
char now_user[10];

void print_msg(void *arg)
{
    char sql[MAX_SIZE];
    pthread_mutex_t mutex;
    int sockfd = *((int *)arg);

    while(1)
    {
        pthread_mutex_lock(&mutex);

	read(sockfd,&msg,sizeof(struct message));

	switch(msg.action)
	{
	    case STO_SUCCESS:
	    {
		rcv_deal();

		break;
	    }
	    case STO_FAIL:
	    {
		sprintf(sql,"用户%s不在线",msg.name);

		remind(sql);

		memset(sql,0,sizeof(sql));
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case STA_SUCCESS:
	    {
	        if(strcmp(msg.name,now_user) != 0)
		{
		    sprintf(sql,"%s(群发):%s\n",msg.name,msg.msg);

		    remind(sql);
		}
		
		memset(sql,0,sizeof(sql));
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case NO_SAY:
	    {
		remind("对不起，你已经被禁言");
                
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case SAY:
	    {
	        remind("恭喜你，已经被解禁");
		
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case OUT:
	    {
	        remind("你已经被管理员强制下线");

		endwin();
	       
		exit(1);

		break;
	    }
	    case CHP_SUCCESS:
	    {
	        remind("密码修改成功！");
		
		memset(&msg,0,sizeof(struct message));

		break;
	    }
	    case CHP_FAIL:
	    {
		remind("原密码错误！");
		
		memset(&msg,0,sizeof(struct message));
		
		break;
	    }
	    case SNF_SUCCESS:
	    {
	        remind("文件传输完毕!");

		memset(&msg,0,sizeof(struct message));

		break;
	    }
	    case SNF:
	    {
		get_file(sockfd);

		break;
	    }
	    default:
	    {
	        break;
	    }
	}
        
	pthread_mutex_unlock(&mutex);
    }
}
int main(int argc, char *argv[]) 
{ 
        int sockfd;
	char sql[MAX_SIZE];
	struct sockaddr_in server_addr; 
	
	if(argc!=2) 
	{ 
		fprintf(stderr,"Usage:%s host name \a\n",argv[0]); 
		exit(1); 
	} 

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{ 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 

	bzero(&server_addr,sizeof(server_addr)); 
	server_addr.sin_family=AF_INET;          
	server_addr.sin_port=htons(portnumber);  
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);  

	
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 
   
        pthread_t id;
	
	system("reset");
	    
        
	while(1)
        {
	    first_table(sockfd);
	    
	    switch(msg.action)
	    {
	        case LOG_SUCCESS:
	        {
	            if(strcmp(msg.name,"admin") == 0) 
	            {   
		        remind("管理员正在登录……");
	                
			pthread_create(&id,NULL,(void *)print_msg,(void *)&sockfd);
		        
			strcpy(now_user,msg.name);
		
		        admin_table(sockfd);

	            }
		    else
		    {
	                sprintf(sql,"用户%s正在登录……",msg.name);
			remind(sql);
                        memset(sql,0,sizeof(sql));
			
			pthread_create(&id,NULL,(void *)print_msg,(void *)&sockfd);
			
			strcpy(now_user,msg.name);

		        user_table(sockfd);
			
	                break;
                    }
		}
	        case LOG_FAIL:
	        {
	            if(!strcmp(msg.name,"admin"))
		    {
	                sprintf(sql,"超级用户%s%s",msg.name,msg.msg);
			remind(sql);
			memset(sql,0,sizeof(sql));
		    }
		    else
		    {
	                sprintf(sql,"用户%s%s",msg.name,msg.msg);
			remind(sql);
			memset(sql,0,sizeof(sql));
		    }
	            
	            break;
	        }
                case LOGIN_SUCCESS:
	        { 
		    if(!strcmp(msg.name,"admin"))
		    {
	                remind("管理员正在初始化……");	

		        admin_table(sockfd);

		    }
		    else
		    {
			sprintf(sql,"用户%s注册成功!您获得id:%d",msg.name,msg.id);
			remind(sql);
			refresh();
			memset(sql,0,sizeof(sql));

			pthread_create(&id,NULL,(void *)print_msg,(void *)&sockfd);
	       
	                strcpy(now_user,msg.name);
		        
			user_table(sockfd);
		        
			break;
	            }
		}
	        case LOGIN_FAIL:
	        {
	            if(!strcmp(msg.name,"admin"))
		    {
		        remind("管理员已初始化!");

		    }
                    else
		    {
			sprintf(sql,"注册失败,用户名%s已被占用",msg.name);
			remind(sql);
			memset(sql,0,sizeof(sql));
		    }
                        
		    break;
	        }
		default:
		{
		    break;
		}
            }
	        
            memset(&msg,0,sizeof(struct message));
	    
	}
} 
