#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 6667
#define BUF_SIZE 128
#define END_CHAT "bye"
#define SERV_IP "127.0.0.1"

void error_msg(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    int sockfd = 0;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    char buffer[BUF_SIZE];    

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error_msg("open socket");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    server_addr.sin_port = htons(PORT);

    for (;;) { 
        printf("Say to Server, End with bye \n");
        scanf("%s", buffer);
        if (sendto(sockfd, buffer, strlen(buffer), 0,
            (struct sockaddr *)& server_addr, addrlen) < 0) {
            error_msg("sendto");
        }

        if (strcmp(buffer, END_CHAT) == 0) {
            break;
        }

        memset(buffer, '\0', sizeof(char) * BUF_SIZE);
        if (recvfrom(sockfd, buffer, BUF_SIZE, 0, 
            (struct sockaddr *) &server_addr, &addrlen) < 0) {
            error_msg("recvfrom");
        }
        printf("From Sever: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
