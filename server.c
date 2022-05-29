#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    printf("Server Program\n");
    char tcpbuffer[50];
    int sockfd, connfd;
    // Create server scoket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address, cli;
    /// Assign IP and PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = 5000;
    int s = sizeof(struct sockaddr_in);
    // Bind newly created socket to given IP
    bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    // Now server is ready to listen
    listen(sockfd, 5);
    // accept the data packet from client
    connfd = accept(sockfd, (struct sockaddr *)&cli, (&s));

    // Code for continuing chat
    do
    {
        printf("\nWaiting for response from client\n");
        recv(connfd, tcpbuffer, sizeof(tcpbuffer), 0);
        printf("Received message from client: %s\n", tcpbuffer);
        printf("Enter your message:Type exit to close chat. \n");
        gets(tcpbuffer);
        send(connfd, tcpbuffer, sizeof(tcpbuffer), 0);
    } 
    // The loop will continue until an exit message is typed from the server side
    while (strcmp(tcpbuffer, "exit") != 0);

    close(connfd);
    close(sockfd);
}