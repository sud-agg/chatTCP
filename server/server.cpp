//server.cpp

#include "server/Server.h"

int Server::getProtNumberForSocket(){
    //Check what port is assigned
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if (getsockname(Server::sock, (struct sockaddr *)&sin, &len) == -1)
        perror("getsockname");
    else
        printf("port number %d\n", ntohs(sin.sin_port));
    return sin.sin_port;
}

int Server::handleSocketWork(){
    Server::sock = 0;
    int sock = 0, clientLen;//, read_size;
    struct sockaddr_in client; //server, client;
    char client_message[200] = {0};
    char message[100] = {0};
    const char *pMessage = "Bye";
    
    Server::sock = initAndBindSocket(Server::sock);
    
    if (Server::sock == 1){
        return 1;
    }
    
    printf("Waiting for incoming connections...\n");
    clientLen = sizeof(struct sockaddr_in);
    
    //Accept connection from an incoming client
    sock = accept(Server::sock, (struct sockaddr *)&client, (socklen_t*)&clientLen);
    if (sock < 0){
        perror("accept failed");
        return 1;
    }
    printf("Connection accepted...\n");

    //Accept incoming connection
    while (1) {
        
        memset(client_message, '\0', sizeof client_message);
        memset(message, '\0', sizeof message);
        
        //Receive reply from the client
        if (recv(sock, client_message, 200, 0)<0){
            printf("received failed...\n");
            break;
        }
        
        printf("Client reply : %s\n", client_message);
        if (strcmp(pMessage, client_message)==0){
            if (send(sock, "Bye", strlen("Bye"), 0)<0){
                printf("Send failed...\n");
            }
            break;
        }
        
        printf("Enter the Message: ");
        gets(message);
        
        //Send back some data
        if (send(sock, message, strlen(message), 0)<0){
            printf("Send failed...\n");
            break;
        }
        
        printf("Message send successful...\n");
    }
    close(sock);
    shutdown(sock, 0);
    shutdown(sock, 1);
    shutdown(sock, 2);
    return 0;
}

