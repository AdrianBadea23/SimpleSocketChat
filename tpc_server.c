#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    char server_message[256];
    char client_message[256];
    
    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create socket");
        exit(1);
    }

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(1);
    }

    // listen for connections
    if (listen(server_socket, 1) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(1);
    }

    // accept a connection
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        perror("Failed to accept connection");
        close(server_socket);
        exit(1);
    }

    while (1) {
        // Clear the buffers
        memset(client_message, 0, sizeof(client_message));
        memset(server_message, 0, sizeof(server_message));
        
        // receive message from client
        int bytes_received = recv(client_socket, client_message, sizeof(client_message), 0);
        if (bytes_received == -1) {
            perror("Receive failed");
            break;
        } else if (bytes_received == 0) {
            printf("Client disconnected\n");
            break;
        }

        if(strcmp(client_message, "exit\n") == 0){
          printf("Exiting!\n");
          break;
        }
        
        printf("Client: %s\n", client_message);

        // get response from server (user input)
        printf("Server: ");
        fgets(server_message, sizeof(server_message), stdin);

        // send message to client
        int bytes_sent = send(client_socket, server_message, strlen(server_message), 0);
        if (bytes_sent == -1) {
            perror("Send failed");
            break;
        }
    }

    // close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
