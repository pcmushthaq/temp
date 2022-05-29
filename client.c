#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    printf("Client Program\n");
    char tcpbuffer[50];
    int sockfd;

    // Create client socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;

    // Assign IP,PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = 5000;

    // Connect cient socket to server socket
    connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    printf("Client is ready to send messages.\n");
    do
    {
        printf("Enter your message:\n");
        gets(tcpbuffer);
        printf("Waiting for reply from server\n");
        send(sockfd, tcpbuffer, sizeof(tcpbuffer), 0);
        recv(sockfd, tcpbuffer, sizeof(tcpbuffer), 0);
        printf("Recieved from server:%s\n", tcpbuffer);

    } while (strcmp(tcpbuffer, "exit") != 0);
}