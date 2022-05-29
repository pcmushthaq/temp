#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    printf("Client Code Running..\n");
    char tcp_buffer[50];
    int sockfd;
    // Create client socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr1;
    // Assign IP,PORT
    addr1.sin_family = AF_INET;
    addr1.sin_addr.s_addr = INADDR_ANY;
    addr1.sin_port = 4444;
    // Connect cient socket to server socket
    connect(sockfd, (struct sockaddr *)&addr1, sizeof(addr1));
    do
    {
        printf("Enter your message:\n");
        gets(tcp_buffer);
        printf("Waiting for reply from server...\n");
        send(sockfd, tcp_buffer, sizeof(tcp_buffer), 0);
        recv(sockfd, tcp_buffer, sizeof(tcp_buffer), 0);
        printf("Recieved from server: %s\n", tcp_buffer);

    } while (strcmp(tcp_buffer, "exit") != 0);
}