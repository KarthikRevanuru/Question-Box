#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>
void *myfunc(void *myvar);
int main()
    {
    pthread_t thread1,thread2,thread3,thread4,thread5;
    int portno1=9999;
    int portno2=9998;
    int portno3=9997;
    int portno4=9996;
    int portno5=9995;
    pthread_create(&thread1,NULL,myfunc,(void*)portno1);
    pthread_create(&thread2,NULL,myfunc,(void*)portno2);
    pthread_create(&thread3,NULL,myfunc,(void*)portno3);
    pthread_create(&thread4,NULL,myfunc,(void*)portno4);
    pthread_create(&thread5,NULL,myfunc,(void*)portno5);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return 0;
    }
void *myfunc(void *portno1)
    {
    int sockfd, newsockfd, clilen,arr[5];
    int size=5,i=0,j=0,k=0,flag=0,p=0,temp=0,r=0;
    char buffer[256];
    char buf[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    else
        printf("\n*******socket Created********** \n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno1);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)              
        error("ERROR on binding");
    else
        printf("\n*******Binding Successful********** \n");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    else
        printf("\n*******Accepting the connection********** \n");
      while(1)
	{
        bzero(buffer,256);
        n = recv(newsockfd,buffer,255,0);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("Port user %d",portno1);
        printf(" has sent message: %s\n",buffer);
        printf("U send message to");
	printf("%d: ",portno1);
        fgets(buf,sizeof(buf),stdin);
        r=send(newsockfd,buf,sizeof(buf),0);
        if(r<0)
            error("ERROR on sending data");
	}
    close(newsockfd);
    close(sockfd);
    return 0;
    }
