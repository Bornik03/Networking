#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8080

int main(void) {
    int s, len;
    char recvBuffer[256];
    char sendBuffer[256];
    struct sockaddr_in servaddr;
    struct sockaddr_in clntaddr;
    socklen_t clntaddrlen;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Create the socket
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Bind the socket to the server address
    if (bind(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Error binding socket");
        close(s);
        exit(1);
    }

    while (1) {
        // Receiving part
        clntaddrlen = sizeof(clntaddr);
        len = recvfrom(s, recvBuffer, sizeof(recvBuffer) - 1, 0, (struct sockaddr*)&clntaddr, &clntaddrlen);
        if (len < 0) {
            perror("Error receiving message");
            close(s);
            exit(1);
        }
        recvBuffer[len] = '\0';
        printf("Received from client: %s\n", recvBuffer);

        // Sending part
        printf("Enter message to send: ");
        fgets(sendBuffer, sizeof(sendBuffer), stdin);
        sendBuffer[strcspn(sendBuffer, "\n")] = '\0';  // Remove newline character
        len = sendto(s, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*)&clntaddr, clntaddrlen);
        if (len < 0) {
            perror("Error sending response");
            close(s);
            exit(1);
        }
    }

    close(s);
    return 0;
}
