// Routing-Algorithm : Link-State

#include "./route_algo.h"

#include <string>
#include <vector>

class RouteLS : public RouteAlgo {
   public:
    int SendRouteMsg(std::string, std::string);
    int RecvRouteMsg(std::string&);
    std::vector<int> JudgePath(int, int);
};