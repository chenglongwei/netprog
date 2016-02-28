#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 6666
#define BUF_SIZE 128

void error(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockfd = 0;
    int newsockfd = 0;
    socklen_t clientlen = 0;
    char buffer[BUF_SIZE];    
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("open socket");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &server_addr, 
        sizeof(struct sockaddr_in)) < 0) {
        error("bind socket");
    }

    if (listen(sockfd, 5) < 0) {
        error("listen socket");
    }
    
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientlen);

    memset(buffer, '\0', sizeof(char) * BUF_SIZE);
    if (read(newsockfd, buffer, sizeof(char) * BUF_SIZE) < 0) {
        error("read from socket");
    }

    printf("Client: %s\n", buffer);
    scanf("%s", buffer);
    if (write(newsockfd, buffer, strlen(buffer)) < 0) {
        error("write to socket");
    }

    close(newsockfd);
    close(sockfd);
    
    return 0;
}
