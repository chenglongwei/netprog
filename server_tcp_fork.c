#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 6666
#define BUF_SIZE 128

void server_service(int sock);
void error_msg(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockfd = 0;
    int newsockfd = 0;
    socklen_t clientlen = 0;
    int pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    if (listen(sockfd, 5) < 0) {
        error_msg("listen socket");
    }
    
    for (;;) {
        memset(&client_addr, 0, sizeof(struct sockaddr_in));
        if ((newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, 
                          &clientlen)) < 0) {
            error_msg("accecpt socket");
        }
        
        if ((pid = fork()) < 0) {
            error_msg("fork");
        }
        
        // child process
        if (pid == 0) {
            close(sockfd);
            server_service(newsockfd);
            exit(0);
        } else {
            // parent process
            close(newsockfd);
        }
    }

    // parent always hold this sockfd, actually not closed
    close(sockfd);
    return 0;
}

void server_service(int sock) {
    char buffer[BUF_SIZE];
    memset(buffer, '\0', sizeof(char) * BUF_SIZE);
    
    if(read(sock, buffer, BUF_SIZE) < 0) {
        error_msg("read");
    }

    if (write(sock, buffer, strlen(buffer)) < 0) {
        error_msg("write");
    }
}
