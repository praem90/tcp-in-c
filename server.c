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

    printf("Client says %s \n", buff);
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

    printf("Preparing to bind the socket to address \n");
    if(bind(isocket, (SA*) &remote, sizeof(remote)) < 0) {
        printf("Could not bound to socket");
        return 1;
    }
    printf("Bounded to the ip\n");

    if (listen(isocket, 5) != 0) {
        printf("Unable to listen to the socket");
        return 1;
    }

    printf("Listening for clients\n");

    socklen_t len = sizeof(client);
    int csocket = accept(isocket, (SA*) &client, &len);
    if (csocket <= 0) {
        printf("Unable to accept a client %d", csocket);
        return 1;
    }

    char client_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, len);

    printf("Connected to a client %s\n", client_ip);

    char buff[80] ;
    while(1) {
        read_msg(csocket);
        printf("Enter your message:");
        fgets(buff, 80, stdin);
        send(csocket, &buff, sizeof(buff), MSG_EOR);
    }
}


