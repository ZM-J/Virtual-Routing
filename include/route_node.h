// NormalNode : Exchange route information to each-other
#include "./args.h"
#include "./route_algo.h"
#include "./route_message.h"

#include <initializer_list>
#include <map>
#include <vector>

/**
 * RouteNode
 * Usage:
 *  RouteNode n;
 *  n.SetRouteAlgoType(RouteAlgoType::LS);
 *  n.SetActionMode(ActionMode::NORMAL); (NORMAL, CLIENT, CONTROLLER)
 *  n.Start();
 * Cannot Start() before BOTH RouteAlgoType & ActionMode is SPECIFIED.
 */
class RouteNode {
   public:
    RouteNode();
    ~RouteNode();
    int Start();
    int Stop();

    int SetRouteAlgoType(RouteAlgoType);
    int SetActionMode(ActionMode);

   protected:
    // RouteAlgoType : cannot Start() if not set
    RouteAlgoType algo_type_;
    std::shared_ptr<RouteAlgo> route_algo_;
    // ActionMode : cannot Start() if not set
    ActionMode action_mode_;

   private:
    bool running_;

    int WaitForCommands();

    int AddDirectConnection(std::initializer_list<int>);
    int DeleteDirectConnection(std::initializer_list<int>);
    int JoinTopo();
    int LeaveTopo();
};