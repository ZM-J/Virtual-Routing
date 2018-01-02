// base class for different routing algorithm

#include "./args.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class RouteAlgo {
   public:
    virtual int UpdateRouteMsg(const std::string&) = 0;
    virtual vector<pair<string, string>> GenerateRouteMsg() = 0;
    virtual std::vector<int> JudgePath(int, int) = 0;

    // Receive a string message which is a Reachability raw Message
    int UpdateConnectivity(const std::string&);

   protected:
    RouteAlgo() = default;
    ~RouteAlgo() = default;
    std::vector<std::vector<int>> route_table_;
    std::vector<std::vector<int>> connectivity_table_;
};