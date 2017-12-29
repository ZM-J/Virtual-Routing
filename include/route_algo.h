// base class for different routing algorithm

#include <string>
#include <vector>

class RouteAlgo {
   public:
    virtual int SendRouteMsg(std::string, std::string) = 0;
    virtual int RecvRouteMsg(std::string&) = 0;
    virtual std::vector<int> JudgePath(int, int) = 0;

   protected:
    std::vector<std::vector<int> > routeTable;
    virtual std::string serializeMsg(std::vector<std::vector<int> >&) = 0;
    virtual std::vector<std::vector<int> > parseMsg(std::string) = 0;
};