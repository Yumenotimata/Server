#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SERVER_IP "127.0.0.1"


int main(void) {

    

    int rcvSocket, sendSocket;
    struct sockaddr_in serverAddr,client;
    int len;
    printf("server started\n");
    printf("\n");
    /* make socket */
    rcvSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(rcvSocket == -1)
    {
        printf("socket error\n");
    }
    
    printf("socket opended\n");

    /* socket setting */
    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    /* binding socket */    
    if(bind(rcvSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        printf("bind error\n");
        return -1;
    }

    printf("bind succeed\n");

    /* listen socket */
    listen(rcvSocket, 5);

    /* accept TCP connection from client */
    len = sizeof(client);
    if(sendSocket = accept(rcvSocket,(struct sockaddr *)&client,&len) == -1)
    {
        printf("accept error\n");
        return -1;
    }

    printf("accept succeed\n");

    /* send message */
    write(sendSocket, "HTTP1.1 300 OK", 14);

    /* close TCP session */
    close(sendSocket);
    close(rcvSocket);

    return 0;
}