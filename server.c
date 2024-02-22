#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int sd,cd,count=0,i;
	char rbuf[100]={0};
	struct sockaddr_in addr;
	sd = socket(AF_INET,SOCK_STREAM,0);//0- protocol parameter[OS chooses the appropriate protocol based on socket type and address family]
	printf("sd = %d\n",sd);
	printf("socket created\n");

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.1.138.168");
	addr.sin_port = 8999;
	if((bind(sd,&addr,sizeof(addr)))==-1)
	{
		perror("");
		exit(0);
	}
	printf("socket binded with ip and port number\n");

	listen(sd,10);
	printf("socket is in listen mode\n");
	printf("waiting for clients\n");
	while(1)
	{
		cd = accept(sd,0,0);//0,0-address and address length of client socket(here it is ignoring the client address) 
		printf("client request accepted\n");
		count++;
		i=fork();
		if(i==0)
		{
			while(1)
			{
				read(cd,rbuf,100);
				printf("read data from client %d = %s\n",count,rbuf);
			}
		}
		else
		{
			close(cd);
		}
	}
	close(sd);
}
