#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/ioctl.h>

#define PORT 6666
#define BUF_SIZE 128
#define END_CHAT "bye"
#define POLL_SIZE 32

void server_service(int sockfd);
void error_msg(const char *msg) {
    printf("ERROR, %s\n", msg);
    exit(-1);
}

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockfd = 0;
    int newsock;
    unsigned int alen;
    
    struct pollfd poll_set[POLL_SIZE];
    int numfds = 0;

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
    
    memset(poll_set, 0, sizeof(poll_set));
    poll_set[0].fd = sockfd;
    poll_set[0].events = POLLIN;
    numfds++;

    for (;;) {
        int fd_index;
        int nread = 0;
        poll(poll_set, numfds, -1);
        
        for (fd_index = 0; fd_index < numfds; fd_index++) {
            if (poll_set[fd_index].revents & POLLIN) {
                if(poll_set[fd_index].fd == sockfd) {
                    newsock = accept(sockfd, (struct sockaddr *) &client_addr, &alen);
                    if (newsock < 0) {
                        error_msg("accept");
                    }
                    //Add client on fd. 
                    poll_set[numfds].fd = newsock;
                    poll_set[numfds].events = POLLIN;
                    numfds++;
                } else {
                    server_service(poll_set[fd_index].fd);
                    int i = fd_index;
                    for (i = fd_index; i < numfds - 1; i++) {
                        poll_set[fd_index] = poll_set[i + 1];
                    }
                    numfds--;
                }       
            }
        }
    }
    close(sockfd);
    return 0;
}

void server_service(int newsockfd) {
    char buffer[BUF_SIZE];
    for(;;) {
        memset(buffer, '\0', sizeof(char) * BUF_SIZE);

        if (read(newsockfd, buffer, sizeof(char) * BUF_SIZE) < 0) {
            error_msg("read from socket");
        }

        printf("Client: %s\n", buffer);
        if (strcmp(buffer, END_CHAT) == 0) {
            close(newsockfd);
            return;
        }

        printf("Say something to client: \nServer: ");
        scanf("%s", buffer);
        if (write(newsockfd, buffer, strlen(buffer)) < 0) {
            error_msg("write to socket");
        }
    }    
}
