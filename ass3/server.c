#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int welcomeSocket, newSocket;
    char buffer[100];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // Create the socket.
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (welcomeSocket < 0)
    {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully.\n");

    // Set the IP and PORT, Note that we are using the same port as in the client code
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the address struct to the socket
    bind(welcomeSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // Listen on the socket, with 5 max connection requests queued
    listen(welcomeSocket, 5);

    // Accept call creates a new socket for the incoming connection
    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *)&serverStorage, &addr_size);
    printf("Welcome to the chat app. Send close to close the chat.\n");

    do
    {
        printf("Waiting for message from client...\n");
        recv(newSocket, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);
        printf("Enter your message: \n");
        gets(buffer);
        // Send message to the socket of the incoming connection
        send(newSocket, buffer, sizeof(buffer), 0);
    } while (strcmp(buffer, "close") != 0);
    printf("Closing Connections");
    close(newSocket);
    close(welcomeSocket);

    return 0;
}
