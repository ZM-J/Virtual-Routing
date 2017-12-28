#include "Node.hpp"
#include "RouteDV.hpp"
#include "RouteLS.hpp"

#include <initializer_list>
#include <vector>

using namespace std;

RouteNode::RouteNode() {
    algoType = RouteAlgoType::NONE_Algo;
    actionMode = ActionMode::NONE_Action;
    running = false;
}

RouteNode::~RouteNode() {
    // release the memory of RouteAlgo
    routeAlgo = nullptr;
}

int RouteNode::Start() {
    bool check_ok = true;
    if (algoType == RouteAlgoType::NONE_Algo) {
        check_ok = false;
        cout << "Routing Algorithm hasn\'t been specified. (LS, DV)" << endl;
    }
    if (actionMode == ActionMode::NONE_Action) {
        check_ok = false;
        cout << "Action Mode hasn\'t been specified. (NORMAL, CLIENT, "
                "CONTROLLER)"
             << endl;
    }
    if (!check_ok) return;
    while (running) {
        // Send & Recv Routing Msg periodically
    }
    return 0;
}

int RouteNode::Stop() {
    running = false;
    return 0;
}

int RouteNode::SetRouteAlgoType(RouteAlgoType t) {
    if (t == algoType) return;
    routeAlgo = nullptr;
    switch
        t {
            case RouteAlgoType::LS:
                routeAlgo = make_shared<RouteLS>();
                break;
            case RouteAlgoType::DV:
                routeAlgo = make_shared<RouteDV>();
                break;
        }
    algoType = t;
    return 0;
}

int RouteNode::SetActionMode(ActionMode am) {
    if (am == actionMode) return;
    actionMode = am;
    return 0;
}

int RouteNode::AddDirectConnection(initializer_list<int> conl) {
    // Modify the local topo table;
    // ..
    return 0;
}

int RouteNode::DeleteDirectConnection(initializer_list<int> conl) {
    // Modify the local topo table;
    // ..
    return 0;
}

int RouteNode::JoinTopo() {
    // Modify the local topo table;
    // ..
    return 0;
}

int RouteNode::LeaveTopo() {
    // Modify the local topo table;
    // ..
    return 0;
}