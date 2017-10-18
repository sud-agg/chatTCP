//server.h

#ifndef Server_h
#define Server_h

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Server{
private:
    //Socket creation
    short socketCreate(void){
        short hSocket;
        printf("Create the socket\n");
        //AF_INET - define protocol type, SOCK_STREAM - define stream type
        hSocket = socket(AF_INET, SOCK_STREAM, 0);
        return hSocket;
    }
    
    //Bind socket with client port
    int bindCreatedSocket(int hSocket){
        int iRetval = -1;
        int clientPort = 0;
        struct sockaddr_in remote={0};
        
        remote.sin_family = AF_INET; //Internet address family
        remote.sin_addr.s_addr = htonl(INADDR_ANY); //Any incoming interface
        remote.sin_port = htons(clientPort); //Local port
        iRetval = bind(hSocket, (struct sockaddr *)&remote, sizeof(remote));
        
        return iRetval;
    }
    
    int initAndBindSocket(int socket_desc){
        //Create socket
        socket_desc = socketCreate();
        if (socket_desc == -1){
            printf("Can't create socket...\n");
            return 1;
        }
        printf("Yooo... socket created...\n");
        
        //Bind
        if (bindCreatedSocket(socket_desc) < 0){
            printf("Bind failed...\n");
            return 1;
        }
        printf("Bind successful...\n");
        
        //Listen
        listen(socket_desc, 3);
        
        return socket_desc;
    }
    
public:
    int sock;
    int getProtNumberForSocket();
    int handleSocketWork();
};

#endif /* Server_h */
