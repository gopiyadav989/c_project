// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "arcfour.h"

void error(const char*msg){
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]){

    if(argc < 2){
        fprintf(stderr, "port no. not provided \n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in serv_addr, cli_addr;  //give internet address
    socklen_t clilen;   // fronm socket.h, 32bit

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        error("error opening socket");
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));   // bzero - clears

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);   //host to network shot;

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Binding failed");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // newsockfd = accept(int, struct sockaddr *, socklen_t *)
    newsockfd = accept(sockfd, (struct sockaddr *)& cli_addr, &clilen);

    if(newsockfd < 0 ){
        error("Error on accept");
    }

    while(1){
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);     //corresponding have write function of this

        if(n<0){
            error("Error on reading");
        }

        printf("Clint: %s\n", buffer);
        fgets(buffer, 255, stdin);  // input here

        n = write(newsockfd, buffer, strlen(buffer));

        if(n<0){
            error("Error on writing");
        }
        int i = strncmp("Bye", buffer,3);
        if(i == 0){
            break;
        }
    }

    close(newsockfd);
    close(sockfd);
    return 0;



}
