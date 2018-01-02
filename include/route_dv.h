// Routing-Algorithm : Distance-Vector
#ifndef VIRTUAL_ROUTING_ROUTE_DV
#define VIRTUAL_ROUTING_ROUTE_DV

#include "./route_algo.h"

#include <string>
#include <vector>

class RouteDV : public RouteAlgo {
   public:
    int SendRouteMsg(std::string, std::string);
    int RecvRouteMsg(std::string&);
    std::vector<int> JudgePath(int, int);

   protected:
    std::vector<std::vector<int> > routeTable;
    std::string serializeMsg(std::vector<std::vector<int> >&);
    std::vector<std::vector<int> > parseMsg(std::string);
};

#endif