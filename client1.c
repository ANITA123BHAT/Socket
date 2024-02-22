#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int sd;
	char buf[100]={0};
	struct sockaddr_in addr;
	sd = socket(AF_INET,SOCK_STREAM,0);
	printf("sd = %d\n",sd);
	printf("socket created\n");

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.1.138.168");
	addr.sin_port = 8999;
	if(connect(sd,&addr,sizeof(addr)) == -1)
	{
		perror("");
	}
	else
	{
		printf("server accepted the connection\n");
		while(1)
		{
			scanf("%s",buf);
			write(sd,buf,strlen(buf)+1);
			printf("client writes\n");
		}
	}
	close(sd);

}
