// client.c
/*
filename server_ipaddress portno
argv[0] - filename
argv[1] - server_ipaddress
*/
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "arcfour.h"

#define F fflush(stdout);
#define BUFFER_SIZE 1024
#define PORT 8080

void error(const char*msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    int sockfd, portno, n;
    char *buffer;
    int buffer_size = BUFFER_SIZE;

    struct sockaddr_in serv_addr;  // from <netinet/in.h>
    struct hostent *server; //form <netdb.h>

    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        error("Memory allocation failed");
    }

    if(argc != 2){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = PORT;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("ERRor in opening socket");
    }

    // Resolve hostname
    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr, "Error, no such host");
        exit(1);
    }

    // Set up server address
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family =  AF_INET;
    bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Connect to server
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
        error("Connection Failed");
    }

    // Initialize encryption
    char* key; int16 keyLen;
    key = "tomatoes";
    keyLen = strlen(key);
    Arcfour *rc4 = rc4init((int8*) key, keyLen);
    int16 cBlen;
    int8 *decrypted;
    int8 *encrypted;

    struct timeval timeout;
    timeout.tv_sec = 30;  // 30 seconds
    timeout.tv_usec = 0;  // 0 microseconds
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        error("setsockopt failed");
    }

    // Main communication loop
    while(1){
        bzero(buffer, buffer_size);
        printf("Enter message: ");
        if (fgets(buffer, buffer_size - 1, stdin) == NULL) {
            error("Error reading from stdin");
        }

        // Encrypt before sending
        cBlen = strlen(buffer);
        encrypted = rc4encrypt(rc4, (int8*) buffer, cBlen);

        n = write(sockfd, encrypted, buffer_size-1);
        if(n<0){
            error("Error on writing");
        }
        bzero(buffer, buffer_size);
        n = read(sockfd, buffer, buffer_size-1);
        if (n < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                printf("Timeout: No response from client for 10 seconds.\n");
                break;
            } else {
                error("Error reading from socket");
            }
        }

        cBlen = strlen(buffer);
        decrypted = rc4decrypt(rc4, (int8*) buffer, cBlen);
        printf("Server: %s", decrypted);

        int i = strncmp("bye", (char*)decrypted,3);
        if(i == 0){
            break;
        }
    }

    rc4uninit(rc4);
    free(buffer);
    close(sockfd);

    return 0;
}
