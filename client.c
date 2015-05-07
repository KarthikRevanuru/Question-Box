#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h> 
#include<netdb.h>  

void error(char *msg)
{ 
   perror(msg);    
exit(0);
}

int main(int argc, char *argv[]){    
	int sockfd, portno, n,i=0;    
	struct sockaddr_in serv_addr;    
	struct hostent *server;    
	char buffer[256],buff[256];
	int *p=NULL;  
  
	if (argc < 3) {
	  	fprintf(stderr,"usage %s hostname port\n", argv[0]); 
		exit(0);    
	}    
	portno = atoi(argv[2]);    

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    
	if (sockfd < 0)        
         error("ERROR opening socket");
           else
         printf("*******successfully Created the Port********** \n");  
        server = gethostbyname(argv[1]);    
	if (server == NULL) { 
       fprintf(stderr,"ERROR, no such host\n");
      exit(0);  
          } 
          else 
          printf("     *******Host Found********** \n"); 
          
	bzero((char *) &serv_addr, sizeof(serv_addr));    
	serv_addr.sin_family = AF_INET;    
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr
		, server->h_length);    
	serv_addr.sin_port = htons(portno);    

	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)  
		error("ERROR connecting");  
            else
            printf("*******successful connection to the Port********** \n"); 
 
	//printf("Please enter the Numbers to be Sorted: ");
	while(1){   
	printf("Send your message: "); 
	bzero(buffer,256);
           fgets(buffer,255,stdin);    
	n = send(sockfd,buffer,strlen(buffer),0);    
	if (n < 0)  
         error("ERROR writing to socket");    
	bzero(buffer,256);
          //printf("The Sorted List Recieved from the Server is :\n") ;   
	n = recv(sockfd,buff,sizeof(buff),0);	
                  printf("Message from server: %s",buff);
	if (n < 0)
        error("ERROR reading from socket");    
	printf("%s",buffer);
          }
	close(sockfd);  
	return 0;
} 
