#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

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


  fd_set sockets;
  FD_ZERO(&sockets);
  FD_SET(sockfd,&sockets);
  FD_SET(STDIN_FILENO, &sockets);

  struct sockaddr_in serveraddr, clientaddr;
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(ports);
  serveraddr.sin_addr.s_addr=inet_addr(ip);

  int e = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  if(e<0){
    printf("There was an error connecting\n");
    return 1;
  }
  printf("Please enter a message for the server:\n");

while(1){

    int len=sizeof(clientaddr);
  	fd_set tmp_set = sockets;
  	select(FD_SETSIZE,&tmp_set, NULL, NULL, NULL);
  	int i;

  	for(i=0; i<FD_SETSIZE;i++){
  		if(FD_ISSET(i,&tmp_set)){
            if(i == STDIN_FILENO){
  			  char input[5000];
  			  fgets(input,5000,stdin);
  			  printf("\nSending to server: %s",input);
  			  send(sockfd,input,strlen(input)+1,0);
  			  if(strcmp(input, "quit")==0){
  			    close(i);
  			    FD_CLR(i,&sockets);
  			    return 0;
  			  }
            }
  			else if(i==sockfd){
              char line[5000];
  		      recv(i,line,5000,0);
  			  printf("Got from server: %s\n",line);
  			  printf("size: %d",strlen(line));
  			  if(strcmp(line, "quit")==0){
                 close(i);
                 FD_CLR(i,&sockets);
                 return 0;
              }
  			}
  		}
  	}
 }
return 0;
} 
