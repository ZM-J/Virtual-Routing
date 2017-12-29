// NormalNode : Exchange route information to each-other
#include "./Args.hpp"
#include "./RouteAlgo.hpp"

#include <initializer_list>
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

    int AddDirectConnection(std::initializer_list<int>);
    int DeleteDirectConnection(std::initializer_list<int>);

    int JoinTopo();
    int LeaveTopo();

   protected:
    // RouteAlgoType : cannot Start() if not set
    RouteAlgoType algoType_;
    std::shared_ptr<RouteAlgo> routeAlgo_;
    // ActionMode : cannot Start() if not set
    ActionMode actionMode_;

    std::vector<std::vector<int> > routeTable_;

   private:
    bool running_;
};