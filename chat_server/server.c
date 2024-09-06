// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "arcfour.h"
#include <errno.h>

#define F fflush(stdout);
#define BUFFER_SIZE 1024
#define PORT 8080

void error(const char*msg){
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]){

    int sockfd, newsockfd, portno, n;
    char *buffer;
    int buffer_size = BUFFER_SIZE;

    struct sockaddr_in serv_addr, cli_addr;  //give internet address
    socklen_t servlen, clilen;   // from socket.h, 32bit

    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        error("Memory allocation failed");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        error("error opening socket");
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));   // bzero - clears
    portno = PORT;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);   //host to network shot;

    servlen = sizeof(serv_addr);
    //int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    if(bind(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0){
        error("Binding failed");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // newsockfd = accept(int, struct sockaddr *, socklen_t *)
    newsockfd = accept(sockfd, (struct sockaddr *)& cli_addr, &clilen);

    if(newsockfd < 0 ){
        error("Error on accept");
    }

    // Initialize encryption
    char* key; int16 keyLen;
    key = "tomatoes";
    keyLen = strlen(key);
    Arcfour *rc4 = rc4init((int8*) key, keyLen);
    int16 cBlen;
    int8 *decrypted;
    int8 *encrypted;

    // Set up the socket with a timeout for receiving data
    struct timeval timeout;
    timeout.tv_sec = 30;  // 30 seconds
    timeout.tv_usec = 0;  // 0 microseconds

    // Set up the socket with a timeout for receiving data
    if (setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        error("setsockopt failed");
    }

    FILE *chat_log = fopen("server_chat_log.txt", "a");
    if(chat_log == NULL){
        error("error in opening the file");
    }

    while(1){
        bzero(buffer, buffer_size);

        n = read(newsockfd, buffer, buffer_size-1); //corresponding have write function of this
        if (n < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                printf("Timeout: No response from client for 10 seconds.\n");
                break;
            } else {
                error("Error reading from socket");
            }
        }

        // Decrypt the received message
        cBlen = strlen(buffer);
        decrypted = rc4decrypt(rc4, (int8*) buffer, cBlen);
        printf("Clint: %s", decrypted); F;
        fprintf(chat_log, "Client (received): %s\n", decrypted);

        bzero(buffer, buffer_size);
        printf("Enter message: "); F;
        fgets(buffer, buffer_size - 1, stdin); // input here

        // Encrypt before sending
        cBlen = strlen(buffer);
        encrypted = rc4encrypt(rc4, (int8*) buffer, cBlen);
        n = write(newsockfd, encrypted, buffer_size-1);

        if(n<0){
            error("Error writing to socket");
        }

        fprintf(chat_log, "Server (sent): %s\n", buffer);

        int i = strncmp("bye", buffer,3);
        if(i == 0){
            break;
        }
    }

    rc4uninit(rc4);
    free(buffer);
    fclose(chat_log);
    close(newsockfd);
    close(sockfd);
    return 0;
}
