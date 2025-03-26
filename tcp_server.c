// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[MAX];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(0);
    }
    printf("Socket created\n");  // Print when the socket is created successfully

    // Set up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(0);
    }
    printf("Socket binded\n");  // Print when binding is successful

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(0);
    }
    printf("Server is running and waiting for client connection...\n");

    // Accept client connection
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("Accept failed");
        exit(0);
    }

    // Receive and reply to client messages
    while (1) {
        bzero(buffer, MAX);

        // Read message from the client
        read(client_fd, buffer, sizeof(buffer));
        printf("Client: %s\n", buffer);

        // If the client sends "exit", break the loop and close the connection
        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server exit...\n");
            break;
        }

        // Send a response back to the client
        printf("Enter a response to send to the client: ");
        bzero(buffer, MAX);
        fgets(buffer, MAX, stdin); // Get response from the server
        write(client_fd, buffer, sizeof(buffer)); // Send to client
    }

    // Close the socket
    close(client_fd);
    close(server_fd);
    return 0;
}
