#ifndef VIRTUAL_ROUTING_SOCKET_SENDER
#define VIRTUAL_ROUTING_SOCKET_SENDER

#include <netinet/in.h>
#include <string>

class SocketSender {
    struct sockaddr_in server_addr;
    int client_socket_fd;

   public:
    SocketSender();
    ~SocketSender();
    int Send(std::string dest_ip, std::string msg);
};

#endif
