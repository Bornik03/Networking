#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int s, len;
    char* servname;
    int servport;
    char sendBuffer[256];
    char recvBuffer[256+1];
    struct sockaddr_in servaddr;

    servname = "127.0.0.1";
    servport = 8080;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, servname, &servaddr.sin_addr);
    servaddr.sin_port = htons(servport);

    // Create the socket
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(1);
    }

    while (1) {
        // Sending part
        printf("Enter message to send: ");
        fgets(sendBuffer, sizeof(sendBuffer), stdin);
        sendBuffer[strcspn(sendBuffer, "\n")] = '\0';  // Remove newline character
        len = sendto(s, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        if (len < 0) {
            perror("Error sending message");
            close(s);
            exit(1);
        }

        // Receiving part
        len = recvfrom(s, recvBuffer, sizeof(recvBuffer) - 1, 0, NULL, NULL);
        if (len < 0) {
            perror("Error receiving response");
            close(s);
            exit(1);
        }
        recvBuffer[len] = '\0';

        printf("Received from server: %s\n", recvBuffer);
    }

    close(s);
    return 0;
}
