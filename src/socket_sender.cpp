#include "socket_sender.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>
#include "log.h"

// #define SERVER_PORT 5188
#define SERVER_PORT 43967
#define BUFFER_SIZE 2048

SocketSender::SocketSender() {
    client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket_fd < 0) {
        perror("Create Socket Failed!");
        exit(1);
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

SocketSender::~SocketSender() { close(client_socket_fd); }

int SocketSender::Send(std::string dest_ip, std::string msg) {
    const unsigned int num = msg.size();
    if (num > BUFFER_SIZE)
        return -1;
    server_addr.sin_addr.s_addr = inet_addr(dest_ip.c_str());
    // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    char buffer[BUFFER_SIZE];
    memcpy(buffer, msg.data(), num);
    if (sendto(client_socket_fd, buffer, num, 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        debug_log("send msg failed.\n");
    }
    return 0;
}
