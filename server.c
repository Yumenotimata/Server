#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define SERVER_ADDR "127.0.0.1"
#define SIZE (5*1024)

int parseRequestMessage(char *parseMessage,char *request,char *target);
int httpRespond(int sendSocket);
int rcvSocket, sendSocket;
int main(void) {

    
    struct sockaddr_in addr, client;
    int len;
    int ret;

    /* make socket */
    rcvSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (rcvSocket < 0) {
        fprintf(stderr, "Error. Cannot make socket\n");
        return -1;
    }
    
    /* socket setting */
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(8080);
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    /* binding socket */    
    int yes = 1;

    //enable to bind socket 
    if (setsockopt(rcvSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes)) < 0)
    {
        perror("ERROR on setsockopt");
        exit(1);
    }
    ret = bind(rcvSocket, (struct sockaddr *)&addr, sizeof(addr));
    
    if (ret < 0) {
        fprintf(stderr, "Error. Cannot bind socket\n");
        printf("%d",errno);
        return -1;
    }

    /* listen socket */
    listen(rcvSocket, 2);

    /* accept TCP connection from client */
    len = sizeof(client);
    sendSocket = accept(rcvSocket,NULL,NULL);


    /* send message *///write(sendSocket,"HTTP1.1 404 Not Found",15);
    httpRespond(sendSocket);
  
    /* close TCP session */
    close(sendSocket);
    close(rcvSocket);

    return 0;
}


int parseRequestMessage(char *parseMessage,char *request,char *target)
{
    char *line;
    char *tmpRequest;
    char *tmpTraget;

    line = strtok(parseMessage,"\n");

    tmpRequest = strtok(line," ");
    strcpy(request,tmpRequest);

    tmpTraget = strtok(NULL," ");
    strcpy(target,tmpTraget);

    return 0;
}

int httpRespond(int sendSocket)
{
    int requestMessageSize;
    char requestMessage[SIZE];

    char request[SIZE];
    char target[SIZE];

    while(1)
    {
        printf("now receive...\n");
        requestMessageSize = recv(sendSocket,requestMessage,SIZE,0);
        requestMessage[requestMessageSize] = '\0';

        if(requestMessageSize == -1)
        {
            printf("request error\n");
            break;
        }
        if(requestMessageSize == 0)
        {
            printf("connection ended\n");
            break;
        }

        printf("%s\n\n\n",requestMessage);
        parseRequestMessage(requestMessage,request,target);
        printf("request massage :%s %s\n",request,target);
        

    }     

    return 0;
}