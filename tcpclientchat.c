#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

  char ip[20];
  char port[6];
  printf("What is the IP of the server?\n");
  fgets(ip,20,stdin);
  printf("What is the port?\n");
  fgets(port,6,stdin);
  int ports = atoi(port);
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
    printf("There was an error creating the socket\n");
    return 1;
  }

  struct sockaddr_in serveraddr;
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(ports);
  serveraddr.sin_addr.s_addr=inet_addr(ip);

  int e = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  if(e<0){
    printf("There was an error connecting\n");
    return 1;
  }
while(1){
   printf("Enter a line: ");
   char line[5000];
   char line2[5000];
   fgets(line,5000,stdin);
   send(sockfd,line,strlen(line)+1,0);
   recv(sockfd,line2,5000,0);
   printf("%s\n",line2);
   close(sockfd);
 }
return 0;
} 
