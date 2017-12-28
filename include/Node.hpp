// NormalNode : Exchange route information to each-other
#include "./Args.hpp"
#include "./RouteAlgo.hpp"

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
    int SetRouteAlgoType(RouteAlgoType t);
    int SetActionMode(ActionMode am);

    int Start();

   protected:
    // RouteAlgoType : cannot Start() if not set
    RouteAlgoType algoType;
    RouteAlgo *routeAlgo;
    // ActionMode : cannot Start() if not set
    ActionMode actionMode;

    std::vector<std::vector<int> > routeTable;

   private:
};