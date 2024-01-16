#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080  // Same port as server

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    int valread;
    int random_number;

    // Create socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Server details
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.153.129", &serv_addr.sin_addr)<=0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Receive random number from server
    valread = read(sockfd, &random_number, sizeof(random_number));

    printf("Random number from server: %d\n", random_number);

    // Close socket
    close(sockfd);
    return 0;
}
