// base class for different routing algorithm
#ifndef VIRTUAL_ROUTING_ROUTE_ALGO
#define VIRTUAL_ROUTING_ROUTE_ALGO

#include "./args.h"
#include "./thread_safe_queue.h"

#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class RouteAlgo {
   public:
    RouteAlgo() = default;
    ~RouteAlgo() = default;
    virtual int UpdateRouteMsg(const std::string&) = 0;
    // GenereateRouteMsg is to Genereate route msg by itself
    virtual queue<pair<string, string>> GenerateRouteMsg() = 0;
    virtual std::vector<int> JudgePath(int, int) = 0;

    // Receive a string message which is a Reachability raw Message
    int UpdateConnectivity(const std::string&);

    // GetOtherMsgToSend is to broadcast datagrams
    //      received from other nodes (if needed)
    queue<pair<string, string>> GetOtherMsgToSend();

   protected:
    std::vector<std::vector<int>> route_table_;
    std::vector<std::vector<int>> connectivity_table_;
    Queue<pair<string, string>> msg_to_send_;
};

#endif
