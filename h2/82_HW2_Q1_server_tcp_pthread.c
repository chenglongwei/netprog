#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT 6666
#define BUF_SIZE 128
#define END_CHAT "bye"

void *server_service(void *args);
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
    pthread_t pthid;

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
        
        pthread_create(&pthid, NULL, server_service, &newsockfd);
    }

    close(sockfd);
    return 0;
}

void *server_service(void *args) {
    int newsockfd = *((int *)args);
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
