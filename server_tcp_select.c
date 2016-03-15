#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 6666
#define BUF_SIZE 128

void server_service(int sockfd);
void error_msg(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockfd = 0;
    //int newsock;
    fd_set rfds;
    fd_set afds;
    unsigned int alen;
    int fd, nfds;

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
    
    nfds = getdtablesize();
    FD_ZERO(&afds);
    FD_SET(sockfd, &afds);

    for (;;) {
        memcpy(&rfds, &afds, sizeof(rfds));
        if (select(nfds, &rfds, NULL, NULL, NULL) < 0) {
            error_msg("select");
        }
        
        if (FD_ISSET(sockfd, &rfds)) {
            int newsock = accept(sockfd, (struct sockaddr *) &client_addr, &alen);
            if (newsock < 0) {
                error_msg("accept");
            }
            FD_SET(newsock, &afds);
        }

        for (fd = 0; fd < nfds; fd++) {
            if (fd != sockfd && FD_ISSET(fd, &rfds)) {
                server_service(fd); 
                close(fd);
                FD_CLR(fd, &afds);
            }       
        }
    }

    close(sockfd);
    return 0;
}

void server_service(int sock) {
    char buffer[BUF_SIZE];
    memset(buffer, '\0', sizeof(char) * BUF_SIZE);
    
    if (read(sock, buffer, BUF_SIZE) < 0) {
        error_msg("read");
    }

    if (write(sock, buffer, strlen(buffer)) < 0) {
        error_msg("write");
    }
}
