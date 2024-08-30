/*
filename server_ipaddress portno
argv[0] - filename
argv[1] - server_ipaddress
argv[2] - portno
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_BUFFER_SIZE 1024

void error(const char*msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;  // from <netinet/in.h>
    struct hostent *server;

    char buffer[MAX_BUFFER_SIZE];

    if(argc != 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    // Validate port number
    portno = atoi(argv[2]);
    if (portno <= 0) {
        fprintf(stderr, "Invalid port number: %d\n", portno);
        exit(EXIT_FAILURE);
    }


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

    // Main communication loop
    while(1){
        bzero(buffer, MAX_BUFFER_SIZE);
        printf("Enter message: ");
        if (fgets(buffer, 255, stdin) == NULL) {
            error("Error reading from stdin");
        }
        n = write(sockfd, buffer, strlen(buffer) +1);  // +1,Includes null terminator
        if(n<0){
            error("Error on writing");
        }
        bzero(buffer, MAX_BUFFER_SIZE);
        n = read(sockfd, buffer, MAX_BUFFER_SIZE - 1);
        if(n < 0){
            error("Error on reading");
        }
        printf("Server: %s", buffer);

        int i = strncmp("Bye", buffer,3);
        if(i == 0){
            break;
        }
    }

    close(sockfd);

    return 0;
}
