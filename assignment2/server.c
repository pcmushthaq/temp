#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    printf("Server Code Running..\n");
    char tcp_buffer[50];
    int sockfd, connfd;
    // Create server scoket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr1, addr2;
    /// Assign IP and PORT
    addr1.sin_family = AF_INET;
    addr1.sin_addr.s_addr = INADDR_ANY;
    addr1.sin_port = 4444;
    int s = sizeof(struct sockaddr_in);
    // Bind newly created socket to given IP
    bind(sockfd, (struct sockaddr *)&addr1, sizeof(addr1));
    // Now server is ready to listen
    listen(sockfd, 5);
    // accept the data packet from client
    connfd = accept(sockfd, (struct sockaddr *)&addr2, (&s));

    printf("Waiting for response from client\n");
    recv(connfd, tcp_buffer, sizeof(tcp_buffer), 0);
    printf("Received message from client: %s\n", tcp_buffer);
    printf("Enter your reply:\n");
    gets(tcp_buffer);
    send(connfd, tcp_buffer, sizeof(tcp_buffer), 0);
    print("Message sent. Closing Connection..");
    close(connfd);
    close(sockfd);
}