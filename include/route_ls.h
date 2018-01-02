// Routing-Algorithm : Link-State
#ifndef VIRTUAL_ROUTING_ROUTE_LS
#define VIRTUAL_ROUTING_ROUTE_LS

#include "./route_algo.h"
#include "./route_message.h"

#include <map>
#include <queue>
#include <string>

class RouteLS : public RouteAlgo {
   public:
    vector<int> JudgePath(int, int);
    int UpdateRouteMsg(const std::string&);
    queue<pair<string, string>> GenerateRouteMsg();

    // more funcs ...

   private:
    map<string, LSAdvertisement> others_advertisements_;

    // Queue<pair<string, string>> msg_to_send_; inherited from RouteAlgo
};

#endif
