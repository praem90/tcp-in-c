#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SA struct sockaddr

void read_msg(int client) {
    char buff[80];

    recv(client, buff, sizeof(buff), 0);

    printf("Client says %s", buff);
}

int main() {
    struct sockaddr_in remote, client;
    int isocket;

    isocket = socket(AF_INET, SOCK_STREAM, 0);
    if (isocket == -1) {
        printf("Could not create socket");
        return 1;
    }
    printf("Socket has been created \n");

    remote.sin_family = AF_INET;
    remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    remote.sin_port = htons(9899);

    /* printf("Preparing to bind the socket to address \n"); */
    /* if(bind(isocket, (SA*) &remote, sizeof(remote)) < 0) { */
    /*     printf("Could not bound to socket"); */
    /*     return 1; */
    /* } */
    /* printf("Bounded to the ip"); */

    printf("Connecting to the server \n");

    socklen_t len = sizeof(remote);
    int csocket = connect(isocket, (SA*) &remote, len);
    if (csocket!= 0) {
        printf("Unable to accept a client");
        return 1;
    }

    char buff[80];

    while(1) {
        printf("Enter your message:");
        gets(buff);

        send(isocket, buff, sizeof(buff), MSG_OOB);

        buff[0] = '\0';

        recv(isocket, &buff, sizeof(buff), MSG_EOF);
        printf("Server says: %s \n", buff);
    }
}



