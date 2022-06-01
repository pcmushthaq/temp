#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int clientSocket;
    char buffer[100];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // Create the client socket.
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    if(clientSocket < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully.\n");

    // set PORT and IP
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Connect the client socket to the server
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);

    // Sending "Hello to server"
    printf("Sending Hello to server\n");
    strcpy(buffer,"Hello\n");
    send(clientSocket,buffer,sizeof(buffer),0);

    // Read the message from the server into the buffer
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Print the received message
    printf("Data received from server: %s\n", buffer);

    return 0;
}
