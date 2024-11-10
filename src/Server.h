#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

class Server {
public:
    Server(int port, int backlog = 5);
    ~Server();

    bool initialize();
    void waitForConnection();

private:
    int port;
    int backlog;
    int server_fd;
    struct sockaddr_in server_addr;

    bool createSocket();
    bool bindSocket();
    bool listenSocket();
};

#endif // SERVER_H
