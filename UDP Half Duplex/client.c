#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<netinet/in.h>
int main()
{
int s,len;
char* servname;
int servport;
char* string;
char buffer[256+1];
struct sockaddr_in servaddr;
servname="127.0.0.1";
servport=8080;
string="Hello Bornik";
memset(&servaddr,0,sizeof(servaddr));
servaddr.sin_family=AF_INET;
inet_pton(AF_INET,servname, &servaddr.sin_addr);
servaddr.sin_port=htons(servport);
if((s=socket(PF_INET,SOCK_DGRAM,0))<0)
{
perror("Errог");
exit(1);
}
len=sendto(s,string, strlen(string),0, (struct sockaddr*)&servaddr, sizeof(servaddr));
recvfrom(s,buffer, len, 0, NULL, NULL);
buffer[len]='\0';
printf("String rceived: ");
fputs(buffer, stdout);
close(s);
exit(0);
}