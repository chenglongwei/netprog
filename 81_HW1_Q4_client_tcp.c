#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define SERV_IP "127.0.0.1"
#define PORT 6666
#define BUF_SIZE 128
#define END_CHAT "bye"

void error_msg(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    int sockfd = 0;
    char buffer[BUF_SIZE];    
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error_msg("open socket");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    server_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *) &server_addr, 
        sizeof(struct sockaddr_in)) < 0) {
        error_msg("connect socket");
    }

    for (;;) {
        printf("Enter message, end with %s: \nClient: ", END_CHAT);
        scanf("%s", buffer);
        if (write(sockfd, buffer, strlen(buffer)) < 0) {
            error_msg("write to socket");
        }
        if (strcmp(buffer, END_CHAT) == 0) {
            break;
        }

        memset(buffer, '\0', sizeof(char) * BUF_SIZE);
        if (read(sockfd, buffer, sizeof(char) * BUF_SIZE) < 0) {
            error_msg("read from socket");
        }

        printf("Server: %s\n", buffer);
    }
    close(sockfd);
    
    return 0;
}
