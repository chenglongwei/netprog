#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 6667
#define BUF_SIZE 128
#define END_CHAT "bye"

void error_msg(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockfd = 0;
    int newsockfd = 0;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    char buffer[BUF_SIZE];    
    int pid;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error_msg("open socket");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &server_addr, 
        sizeof(struct sockaddr_in)) < 0) {
        error_msg("bind socket");
    }

    for (;;) {
        memset(buffer, '\0', sizeof(char) * BUF_SIZE);
        if (recvfrom(sockfd, buffer, BUF_SIZE, 0, 
            (struct sockaddr *) &client_addr, &addrlen) < 0) {
            error_msg("recvfrom");
        }
        printf("From Client: %s\n", buffer);
        if (strcmp(buffer, END_CHAT) == 0) {
            break;
        }
        
        printf("Say to Client: ");
        scanf("%s", buffer);
        if (sendto(sockfd, buffer, strlen(buffer), 0,
            (struct sockaddr *) &client_addr, addrlen) < 0) {
            error_msg("sendto");
        }
    }

    close(sockfd);
    return 0;
}
