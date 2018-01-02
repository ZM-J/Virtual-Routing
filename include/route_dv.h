// Routing-Algorithm : Distance-Vector
#ifndef VIRTUAL_ROUTING_ROUTE_DV
#define VIRTUAL_ROUTING_ROUTE_DV

#include "./route_algo.h"
#include "./route_message.h"

#include <map>
#include <queue>
#include <string>

class RouteDV : public RouteAlgo {
   public:
    vector<int> JudgePath(int, int);
    int UpdateRouteMsg(const std::string&);
    queue<pair<string, string>> GenerateRouteMsg();

    // more funcs ...

   private:
    map<string, DVAdvertisement> others_advertisements_;

    // Queue<pair<string, string>> msg_to_send_; inherited from RouteAlgo
};

#endif