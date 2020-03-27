#include"header.h"
int main()
{
struct sockaddr_in v,v1;
int sfd,len,r,nsfd,i=0;
char s[100];
int fd,fd1;
mkfifo("f1",0064);
mkfifo("f2",0064);
fd=open("f1",O_RDONLY);
fd1=open("f2",O_WRONLY);
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
v.sin_addr.s_addr=inet_addr("10.0.0.6");    //add ip of pp-pod

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

while(1)
{
if(fork()==0)
{
while(1)
{
read(fd,s,sizeof(s));
write(nsfd,s,strlen(s)+1);

//printf("data=%s\n",s);
//if(strcmp(s,"bye")==0)
// return 0;
}
}
else
{
while(1)
{
read(nsfd,s,sizeof(s));
//printf("data=%s\n",s);
write(fd1,s,strlen(s)+1);
}
}

}
}
