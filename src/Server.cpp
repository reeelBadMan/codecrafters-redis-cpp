//
// Created by delin on 09/11/2024.
//

#include "Server.h"


Server::Server(int port, int backlog) : port(port), backlog(backlog), server_fd(-1) {
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
}

Server::~Server() {
    if (server_fd != -1) {
        close(server_fd);
    }
}


bool Server::createSocket(){
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd<0){
    std::cerr<<"error creating socket\n";
    return false;
    }

    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "setsockopt failed\n";
        return false;
    }

    return true;

}



bool Server::bindSocket() {
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "Failed to bind to port " << port << "\n";
        return false;
    }
    return true;
}

bool Server::listenSocket() {
    if (listen(server_fd, backlog) != 0) {
        std::cerr << "Listen failed\n";
        return false;
    }
    return true;
}

bool Server::initialize() {
    return createSocket() && bindSocket() && listenSocket();
}

void Server::waitForConnection() {
    std::cout << "Waiting for a client to connect...\n";

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_fd < 0) {
        std::cerr << "Failed to accept client connection\n";
    } else {
	send(client_fd, "+PONG\r\n",7,0);
        std::cout << "Client connected\n";
        close(client_fd);
    }
}