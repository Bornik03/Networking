#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8080

int main(void)
{
int s,len;
char buffer[256];
struct sockaddr_in servaddr;
struct sockaddr_in clntaddr;
int clntaddrlen;
memset(&servaddr,0,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERVER_PORT);
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
if((s=socket(PF_INET,SOCK_DGRAM,0))<0)
{
perror("Error");
exit(1);
}
if((bind(s, (struct sockaddr*)&servaddr, sizeof(servaddr)))<0)
{
perror("Error");
exit(1);
}
for(;;)
{
len=recvfrom(s,buffer,sizeof(buffer),0, (struct sockaddr *)&clntaddr, &clntaddrlen);
printf("Received from client: %s\n",buffer);
sendto(s,buffer, len, 0, (struct sockaddr *)&clntaddr, sizeof(clntaddr));
}
}