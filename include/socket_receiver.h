#include <netinet/in.h>
#include <functional>
#include <string>

#include "./route_message.h"

class SocketReceiver {
    struct sockaddr_in server_addr;
    int server_socket_fd;
    bool recv_running_;

   public:
    SocketReceiver();
    ~SocketReceiver();
    int ListenAndReceive(std::function<int(std::string)>,
                         std::function<int(std::string)>,
                         std::function<int(std::string)>);
    void StopReceiving();
};
