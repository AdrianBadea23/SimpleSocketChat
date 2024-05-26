#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  // create a socket
  int network_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (network_socket == -1) {
    perror("Failed to create socket");
    exit(1);
  }

  // specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // connect to the server
  int connection_status =
      connect(network_socket, (struct sockaddr *)&server_address,
              sizeof(server_address));
  if (connection_status == -1) {
    perror("Connection failed");
    close(network_socket);
    exit(1);
  }

  char server_response[256];
  char client_message[256];

  while (1) {
    // Clear the buffers
    memset(server_response, 0, sizeof(server_response));
    memset(client_message, 0, sizeof(client_message));

    // get message from client (user input)
    printf("Client: ");
    fgets(client_message, sizeof(client_message), stdin);

    // send message to server
    int bytes_sent =
        send(network_socket, client_message, strlen(client_message), 0);
    if (bytes_sent == -1) {
      perror("Send failed");
      break;
    }

    if (strcmp(client_message, "exit\n") == 0) {
      printf("Exit now!");
      break;
    }

    // receive response from server
    int bytes_received =
        recv(network_socket, server_response, sizeof(server_response), 0);
    if (bytes_received == -1) {
      perror("Receive failed");
      break;
    } else if (bytes_received == 0) {
      printf("Server disconnected\n");
      break;
    }

    printf("Server: %s\n", server_response);
  }

  // close the socket
  close(network_socket);

  return 0;
}
