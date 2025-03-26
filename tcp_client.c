// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[MAX];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(0);
    }
    printf("Socket created\n");  // Print when socket is created successfully

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(0);
    }
    printf("Connected to the server...\n");  // Print when connection is successful

    // Read message from server
    bzero(buffer, sizeof(buffer));
    read(sock, buffer, sizeof(buffer));

    // Print the message from server
    printf("Received from server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}
