#include"header.h"
int main()
{
struct sockaddr_in v,v1;
int sfd,len,r,nsfd,i=0;
char s[100];
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
perror("socket");
return 0;
}
perror("socket");
printf("sfd=%d\n",sfd);


v.sin_family=AF_INET;
v.sin_port=htons(3000);
v.sin_addr.s_addr=inet_addr("10.0.0.5");      //add ip of nms-pod

len=(sizeof(v));
r=bind(sfd,(struct sockaddr*)&v,len);
if(r<0)
{
perror("bind");
return 0;
}
perror("bind");

listen(sfd,5);
perror("listen");


nsfd=accept(sfd,(struct sockaddr*)&v1,&len);
if(nsfd<0)
{
perror("accept");
return 0;
}
perror("accept");
printf("***************************\n");
while(1)
{

printf("Enter MSG\n");
scanf(" %[^\n]s",s);
write(nsfd,s,strlen(s)+1);

read(nsfd,s,sizeof(s));
printf("MSG Received from REMOTE TERMINAL to NMS through PP :-  %s\n",s);
}
}
