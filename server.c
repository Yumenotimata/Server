#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SIZE (5*1024)

int httpRepond(int sendSocket);

int main(void) {

    int rcvSocket, sendSocket;
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
    ret = bind(rcvSocket, (struct sockaddr *)&addr, sizeof(addr));
    
    if (ret < 0) {
        fprintf(stderr, "Error. Cannot bind socket\n");
        return -1;
    }

    /* listen socket */
    listen(rcvSocket, 5);

    /* accept TCP connection from client */
    len = sizeof(client);
    sendSocket = accept(rcvSocket,NULL,NULL);

    /* send message */
    
    httpRespond(sendSocket);
    /* close TCP session */
    close(sendSocket);
    close(rcvSocket);

    return 0;
}

int httpRespond(int sendSocket)
{
    int requestMessageSize;
    char requestMessage[SIZE];
    while(1)
    {
        printf("now receive...\n");
        requestMessageSize = recv(sendSocket,requestMessage,SIZE,0);
        requestMessage[requestMessageSize] = '\0';
        printf("%s\n",requestMessage);
        exit(1);
    }
}