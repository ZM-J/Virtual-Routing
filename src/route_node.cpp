#include "route_node.h"
#include "RouteDV.hpp"
#include "RouteLS.hpp"

#include <initializer_list>
#include <vector>

using namespace std;

RouteNode::RouteNode() {
    algoType_ = RouteAlgoType::NONE_Algo;
    actionMode_ = ActionMode::NONE_Action;
    running_ = false;
}

RouteNode::~RouteNode() {
    // release the memory of RouteAlgo
    routeAlgo_ = nullptr;
}

int RouteNode::Start() {
    bool check_ok = true;
    if (algoType_ == RouteAlgoType::NONE_Algo) {
        check_ok = false;
        cout << "Routing Algorithm hasn\'t been specified. (LS, DV)" << endl;
    }
    if (actionMode_ == ActionMode::NONE_Action) {
        check_ok = false;
        cout << "Action Mode hasn\'t been specified. (NORMAL, CLIENT, "
                "CONTROLLER)"
             << endl;
    }
    if (!check_ok) return;
    while (running_) {
        // Send & Recv Routing Msg periodically
    }
    return 0;
}

int RouteNode::Stop() {
    running_ = false;
    return 0;
}

int RouteNode::SetRouteAlgoType(RouteAlgoType t) {
    if (t == algoType_) return;
    routeAlgo_ = nullptr;
    switch
        t {
            case RouteAlgoType::LS:
                routeAlgo_ = make_shared<RouteLS>();
                break;
            case RouteAlgoType::DV:
                routeAlgo_ = make_shared<RouteDV>();
                break;
        }
    algoType_ = t;
    return 0;
}

int RouteNode::SetActionMode(ActionMode am) {
    if (am == actionMode_) return;
    actionMode_ = am;
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