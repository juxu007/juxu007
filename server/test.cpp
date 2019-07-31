//mainserver

#include "test.h"

#define MAXBUF 1024
#define QUEUE 10
#define MAXEVENTS 50
#define FDSIZE 100


int main( int argc, char **argv )
{
    const char* addr_server="127.0.0.1";
    int port_server=8000;
    int socketfd=0;
    struct sockaddr_in sockaddr;
    char sendbuffer[MAXBUF];
    char recvbuffer[MAXBUF];

    socketfd=socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd<0)
    {
        perror("socket() error");
        exit(0);
    }

    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    sockaddr.sin_port=htons(port_server);

    if(bind(socketfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr))<0)
    {
        perror("bind() error");
        exit(1);
    }

    if(listen(socketfd, QUEUE)<0)
    {
        perror("listen() error");
        exit(1);
    }

    /*epoll*/
    int epollfd;
    struct epoll_event events[MAXEVENTS];
    int ret;
    memset(sendbuffer, 0, sizeof(sendbuffer));
    memset(recvbuffer, 0, sizeof(recvbuffer));
    epollfd=epoll_create(FDSIZE);
    struct epoll_event ev;
    ev.events = EPOLLIN|EPOLLET;
    ev.data.fd = socketfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, socketfd, &ev);
    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len=sizeof(client_addr);
        ret=epoll_wait(epollfd, events, MAXEVENTS, -1);
        int fd;
        for(int i=0; i<ret; i++)
        {
            fd=events[i].data.fd;
            if((fd==socketfd)&&(events[i].events&EPOLLIN))
            {
                int accfd=accept(socketfd, (struct sockaddr*)&client_addr, &client_addr_len);
                if(accfd<0)
                {
                    perror("accept() error");
                    close(accfd);
                    exit(1);
                }
                else
                {
                    printf("accept a new client: %s:%s", client_addr.sin_addr, client_addr.sin_port);
                    struct epoll_event acc_event;
                    acc_event.events = EPOLLIN|EPOLLET;
                    acc_event.data.fd = accfd;
                    epoll_ctl(epollfd, EPOLL_CTL_ADD, accfd, &acc_event);
                }
            }
            else if(events[i].events&EPOLLIN)
            {
                printf("The client: %s", recvbuffer);
                int read_ret=read(fd, recvbuffer, sizeof(sendbuffer));
                if(read_ret<0)
                {
                    perror("read() error");
                    close(fd);
                    struct epoll_event acc_event;
                    acc_event.events = EPOLLIN|EPOLLET;
                    acc_event.data.fd = fd;
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &acc_event);
                }
                if(read_ret==0)
                {
                    perror("read() over");
                    close(fd);
                    struct epoll_event acc_event;
                    acc_event.events=EPOLLIN|EPOLLET;
                    acc_event.data.fd=fd;
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &acc_event);
                }
                if(read_ret>0)
                {
                    struct epoll_event acc_event;
                    acc_event.events=EPOLLIN|EPOLLET;
                    acc_event.data.fd=fd;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &acc_event);
                }
            }
            else if(events[i].events&EPOLLOUT)
            {
                printf("I'm server: %s", sendbuffer);
                int write_ret=write(fd, sendbuffer, sizeof(sendbuffer));
                if (write_ret<0)
                {
                    perror("write() error");
                    close(fd);
                    struct epoll_event acc_event;
                    acc_event.events=EPOLLOUT|EPOLLET;
                    acc_event.data.fd=fd;
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &acc_event);
                }
                else
                {
                    struct epoll_event acc_event;
                    acc_event.events=EPOLLOUT|EPOLLET;
                    acc_event.data.fd=fd;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &acc_event);
                }
            }
            else
            {
                perror("error");
            }
        }
    }
    close(epollfd);
    close(socketfd);
    /*epoll*/

    /*select*/

    /*select*/

    /*
    struct sockaddr_in client_addr;
    socklen_t client_addr_len=sizeof(client_addr);
    int conn=accept(socketfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if(conn<0)
    {
        perror("accept() error");
        exit(1);
    }

    while(1)
    {
        memset(sendbuffer, 0, sizeof(sendbuffer));
	    memset(recvbuffer, 0, sizeof(recvbuffer));
        int recvlen=recv(conn, recvbuffer, sizeof(recvbuffer), 0);
        printf("The client:");
        fputs(recvbuffer, stdout);
        if(strcmp(recvbuffer, "exit\n")==0)
        break;
        printf("I'm server:");
	    //scanf("%s",sendbuffer);
        fgets(sendbuffer, sizeof(sendbuffer), stdin);
        if(strcmp(sendbuffer, "exit\n")==0)
        break;
        send(conn, sendbuffer, sizeof(sendbuffer), 0);
    }

    close(conn);
    close(socketfd);
    */

    return 0;
}
