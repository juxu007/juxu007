//client socket
#include"client.h"

#define BUFFER 1024

int main(void)
{
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8000);

    int sock_cli=socket(AF_INET, SOCK_STREAM, 0);
    if(connect(sock_cli, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0)
    {
        perror("connect() error");
        exit(1);
    }

    char sendbuffer[BUFFER];
    char recvbuffer[BUFFER];

    while(1)
    {
        
        /*
        printf("I'm client:");
        fgets(sendbuffer, sizeof(sendbuffer), stdin);
        if(strcmp(sendbuffer, "exit\0")==0)
        break;
        send(sock_cli, sendbuffer, sizeof(sendbuffer), 0);
        recv(sock_cli, recvbuffer, sizeof(recvbuffer), 0);
        printf("The server:");
        fputs(recvbuffer, stdout);
        if(strcmp(recvbuffer, "exit\0")==0)
        break;
        memset(sendbuffer, 0, sizeof(sendbuffer));
        memset(recvbuffer, 0, sizeof(recvbuffer));
        */
    }

    close(sock_cli);

    return 0;
}