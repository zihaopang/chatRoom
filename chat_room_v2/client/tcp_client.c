#include <stdio.h>
#include <errno.h> 
#include <netdb.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/socket.h>

#include "/home/chat_room/include/all.h"

struct message msg;
char now_user[10];

void print_msg(void *arg)
{
    int n_read;
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
                printf("有消息来自用户%s:%s\n",msg.name,msg.msg);
		
		memset(&msg,0,sizeof(struct message));

		break;
	    }
	    case STO_FAIL:
	    {
		printf("用户%s不在线\n",msg.name);
		
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case STA_SUCCESS:
	    {
	        if(strcmp(msg.name,now_user) != 0)
		{
		    printf("用户%s发送群发消息:%s\n",msg.name,msg.msg);
		}
		
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case NO_SAY:
	    {
	        printf("对不起，你已经被禁言\n");
                
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case SAY:
	    {
	        printf("恭喜你，已经被解禁\n");
		
		memset(&msg,0,sizeof(struct message));
	        
		break;
	    }
	    case OUT:
	    {
	        printf("你已经被管理员强制下线\n");
	       
		exit(1);

		break;
	    }
	    case CHP_SUCCESS:
	    {
	        printf("密码修改成功！\n");
		
		memset(&msg,0,sizeof(struct message));

		break;
	    }
	    case CHP_FAIL:
	    {
	        printf("原密码错误！\n");
		
		memset(&msg,0,sizeof(struct message));
		
		break;
	    }
	    case SNF_SUCCESS:
	    {
	        printf("文件传输完毕！\n");
		
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
	    passwd_table();
            
	    passwd_judge(sockfd);
	    
	    switch(msg.action)
	    {
	        case LOG_SUCCESS:
	        {
	            if(strcmp(msg.name,"admin") == 0) 
	            {
	                pthread_create(&id,NULL,(void *)print_msg,(void *)&sockfd);
		        
			printf("\n\t\t\t\t\t管理员正在登录……\n");
		        
			sleep(1);
			
			strcpy(now_user,msg.name);
		
		        system("reset");

		        admin_table();

		        admin_cmd(sockfd);
	            }
		    else
		    {
			printf("\n\t\t\t\t\t用户%s正在登录……\n\t\t\t\t\t",msg.name);
	                
			pthread_create(&id,NULL,(void *)print_msg,(void *)&sockfd);
	       
	                sleep(1);

			strcpy(now_user,msg.name);
        
	                system("reset");

		        welcome_table();

		        input_order(sockfd);
			
	                break;
                    }
		}
	        case LOG_FAIL:
	        {
	            if(!strcmp(msg.name,"admin"))
		    {
		        printf("\n\t\t\t\t\t超级用户%s%s\n",msg.name,msg.msg);
	                
		    }
		    else
		    {
		        printf("\n\t\t\t\t\t用户%s%s\n",msg.name,msg.msg);
		    }
	            
		    sleep(1);

	            system("reset");
			
	            break;
	        }
                case LOGIN_SUCCESS:
	        { 
		    if(!strcmp(msg.name,"admin"))
		    {
			printf("\n\t\t\t\t\t管理员正在登录……\n");
                
		        sleep(1);
		
		        system("reset");

		        admin_table();

		        admin_cmd(sockfd);
		    }
		    else
		    {
		        printf("\n\t\t\t\t\t用户%s注册成功！您获得id:%d,自动登录中……\n",msg.name,msg.id);
	            
		        pthread_create(&id,NULL,(void *)print_msg,(void *)&sockfd);
	       
	                sleep(2);
			
	                strcpy(now_user,msg.name);

	                system("reset");
		        
                        welcome_table();

		        input_order(sockfd);

		        break;
	            }
		}
	        case LOGIN_FAIL:
	        {
	            if(!strcmp(msg.name,"admin"))
		    {
		        printf("\n\t\t\t\t\t管理员已初始化！\n",msg.name);
		    
		    }
                    else
		    {
		        printf("\n\t\t\t\t\t注册失败，用户名%s已被占用\n",msg.name);
		    }
                
		    sleep(2);

	            system("reset");
                        
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
