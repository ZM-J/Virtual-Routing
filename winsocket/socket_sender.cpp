#include "socket_sender.h"

//#include <arpa/inet.h>
//#include <errno.h>
//#include <netdb.h>
//#include <netinet/in.h>
//#include <stdarg.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <unistd.h>

#include <string>

#define SERVER_PORT 43967
#define BUFFER_SIZE 2048

SocketSender::SocketSender() {
    //client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    //if (client_socket_fd < 0) {
    //    perror("Create Socket Failed!");
    //    exit(1);
    //}
    //bzero(&server_addr, sizeof(server_addr));
    //server_addr.sin_family = AF_INET;
    //server_addr.sin_port = htons(SERVER_PORT);
    //// server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

SocketSender::~SocketSender() { /*close(client_socket_fd);*/ }

int SocketSender::Send(std::string dest_ip, std::string msg) {
    //const char *dst_ip = dest_ip.c_str();
    //const char *msg_c = msg.c_str();
    //server_addr.sin_addr.s_addr = inet_addr(dst_ip);
    //char buffer[BUFFER_SIZE];
    //bzero(buffer, BUFFER_SIZE);
    //strncpy(buffer, msg_c,
    //        strlen(msg_c) > BUFFER_SIZE ? BUFFER_SIZE : strlen(msg_c));
    //if (sendto(client_socket_fd, buffer, BUFFER_SIZE, 0,
    //           (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    //    // perror("send msg failed");
    //}
    return 0;
}
