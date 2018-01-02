// base class for different routing algorithm

#include "./args.h"
#include "./route_message.h"
#include "./socket_sender.h"
#include "./thread_safe_queue.h"

#include <map>
#include <string>
#include <vector>

class RouteAlgo {
   public:
    virtual int SendRouteMsg(std::string, std::string) = 0;
    virtual int RecvRouteMsg(std::string&) = 0;

    int StartRecv();
    virtual std::vector<int> JudgePath(int, int) = 0;

   protected:
    RouteAlgo() = default;
    ~RouteAlgo() = default;
    std::vector<std::vector<int>> route_table_;
};