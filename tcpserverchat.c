#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h> 

int main(int argc, char **argv){
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  //file descriptor
  fd_set sockets;
  FD_ZERO(&sockets);
  
  int port;
  printf("What is the port to use for the server?\n");
  scanf("%d", &port);

  struct sockaddr_in serveraddr,clientaddr;
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(port);
  serveraddr.sin_addr.s_addr=INADDR_ANY;

  bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  listen(sockfd,10);
  FD_SET(sockfd, &sockets);
  FD_SET(STDIN_FILENO, &sockets);
  printf("\nPlease enter your message:\n");
  int clientsocket = accept(sockfd,(struct sockaddr*)&clientaddr,&len); 
 while(1){
    
    int len=sizeof(clientaddr);
	fd_set tmp_set = sockets;
	select(FD_SETSIZE,&tmp_set, NULL, NULL, NULL);
	int i;	
        
	for(i=0; i<FD_SETSIZE;i++){
		if(FD_ISSET(i,&tmp_set)){
			if(i==sockfd){
				accept(sockfd,(struct sockaddr*)&clientaddr,&len);
				FD_SET(clientsocket,&sockets);
			}
                        else if(i == STDIN_FILENO){
			  char input[5000];
			  fgets(input,5000,stdin);
			  printf("\nSending to client: %s",input);
			  send(,input,strlen(input)+1,0);
			  printf("\nEnter your message: ");
                        }
			else{
				char line[5000];
				recv(i,line,5000,0);
				printf("Got from client: %s\n",line);
				send(clientsocket,line,strlen(line)+1,0);
				close(i);
				FD_CLR(i,&sockets);
			}
		}
	}
  }
}

