#include <stdlib.h> 
#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sqlite3.h>

#include "/home/chat_room/include/all.h"

struct message msg;
Link head = NULL;

void read_msg(void *arg)
{
    int to_fd;
    int r_len;
    char *errmsg;
    char sql[1024];
    sqlite3 *passwd_db;
    int new_fd = *((int *)arg);
    
    sqlite3_open("/home/chat_room/passwd.db",&passwd_db);
    sqlite3_exec(passwd_db,"create table passwd(id integer,name text,passwd text);",NULL,NULL,&errmsg);

    while(1)
    {
        memset(&msg,0,sizeof(struct message));

	while((r_len = read(new_fd,&msg,sizeof(struct message))) < 0)
        {
            perror("read error!");

            exit(1);
        }
	
	if(r_len == 0)
	{
	    printf("client is close!\n");
            
	    del_user(new_fd);

	    close(new_fd);
            
	    pthread_exit(NULL);
	}
        
	switch(msg.action)
	{
	    case LOGIN:
            {
                login_judge(passwd_db,new_fd);

	        break;
	    }
		        
	    case LOG:
	    {
		log_judge(passwd_db,new_fd);

	        break;
	    }
            case DIS:
	    {
		display_user(new_fd);
		
		break;
	    }
	    case STO:
	    {
		private_chat(new_fd);
		
		break;
	    }
	    case STA:
	    {
	        group_chat(new_fd);

		break;
	    }
	    case SAY:
	    {
	        say(new_fd);

		break;
	    }
	    case NO_SAY:
	    {
		no_say();

		break;
	    }
	    case OUT:
	    {
	        out();

		break;
	    }
	    case CHP:
	    {
	        change_passwd(new_fd,passwd_db);

		break;
	    }
	    case SNF:
	    {
	        send_file(new_fd);

		break;
	    }
	    default:
	    {
	        break;
	    }
	}
    }
}

int main(int argc, char *argv[]) 
{ 
	int r_len;
	int opt = 1;
	int sin_size;
        pthread_t id;
        sqlite3 *save_db;
	int sockfd,new_fd; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr;
	/**/ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	/**/ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); //
	server_addr.sin_family=AF_INET;                 // Internet
//	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // 
	server_addr.sin_addr.s_addr=inet_addr("192.168.1.120");  //
	server_addr.sin_port=htons(portnumber);         // 
        if((setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))) < 0)
	{
	    perror("set socketopt failed!\n");
	    exit(1);
	}
	/**/ 
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	/**/ 
	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
        
	while(1) 
	{ 
		sin_size=sizeof(struct sockaddr_in); 
		
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1) 
		{ 
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
			exit(1); 
		}
		
		pthread_create(&id,NULL,(void *)read_msg,(void *)&new_fd);

		fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr)); 
	} 
	
	close(sockfd); 
	exit(0); 
} 
