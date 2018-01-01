// base class for different routing algorithm

#include "./args.h"

#include <map>
#include <string>
#include <vector>

class RouteAlgo {
   public:
    virtual int SendRouteMsg(std::string, std::string) = 0;
    virtual int RecvRouteMsg(std::string&) = 0;
    virtual std::vector<int> JudgePath(int, int) = 0;

   protected:
    std::vector<std::vector<int>> route_table_;
    std::map<std::string, ReachabilityEnum> connectivity_;
    int SendConnectionCheck();
    int RecvConnectionCheck();
};