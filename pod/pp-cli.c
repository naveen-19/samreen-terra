#include"header.h"
int main()
{
struct sockaddr_in v;
int sfd,len,r;
int fd,fd1;
mkfifo("f1",0064);
mkfifo("f2",0064);
fd=open("f1",O_WRONLY);
fd1=open("f2",O_RDONLY);
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
v.sin_port=htons(3000);
v.sin_addr.s_addr=inet_addr("10.0.0.5");      //add ip of nms-pod
len=(sizeof(v));
r=connect(sfd,(struct sockaddr*)&v,len);
if(r<0)
{
perror("connect");
return 0;
}
perror("connect");
printf("****************************************\n");
while(1)
{
if(fork())
{
while(1)
{
read(sfd,s,sizeof(s));
printf("MSG Received from NMS forworded to REMOTE TERMINAL :-  %s\n",s);
write(fd,s,strlen(s)+1);
}
}
else
{
while(1)
{
read(fd1,s,sizeof(s));
printf("MSG Received from REMOTE TERMINAL forworded to NMS :-  %s\n",s);
write(sfd,s,strlen(s)+1);
}
}
}
}
