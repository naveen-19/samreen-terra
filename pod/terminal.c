#include"header.h"
int main()
{
struct sockaddr_in v;
int sfd,len,r;
char s[100],s1[100];
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
perror("socket");
return 0;
}
perror("socket");
printf("sfd=%d\n",sfd);


v.sin_family=AF_INET;
v.sin_port=htons(4000);
v.sin_addr.s_addr=inet_addr("10.0.0.6");     // add ip of pp-pod

len=(sizeof(v));
r=connect(sfd,(struct sockaddr*)&v,len);
if(r<0)
{
perror("connect");
return 0;
}
perror("connect");

printf("************************************\n");

while(1)
{
read(sfd,s,sizeof(s));
printf("MSG Received from NMS to REMOTE TERMINAL through PP :-  %s\n",s);
if(strcmp(s,"bye")==0)
 return 0;

printf("Enter MSG\n");
scanf(" %[^\n]s",s);
write(sfd,s,strlen(s)+1);
}
}
