#include "route_node.h"
#include "route_dv.h"
#include "route_ls.h"

#include <initializer_list>
#include <vector>

using namespace std;

RouteNode::RouteNode() {
    algo_type_ = RouteAlgoType::NONE_Algo;
    action_mode_ = ActionMode::NONE_Action;
    running_ = false;
}

RouteNode::~RouteNode() {
    // release the memory of RouteAlgo
    route_algo_ = nullptr;
}

int RouteNode::Start() {
    bool check_ok = true;
    if (algo_type_ == RouteAlgoType::NONE_Algo) {
        check_ok = false;
        cout << "Routing Algorithm hasn\'t been specified. (LS, DV)" << endl;
    }
    if (action_mode_ == ActionMode::NONE_Action) {
        check_ok = false;
        cout << "Action Mode hasn\'t been specified. (NORMAL, CLIENT, "
                "CONTROLLER)"
             << endl;
    }
    if (!check_ok) return;
    while (running_) {
        // Send & Recv Routing Msg periodically
        // Reachability Message Exchange

        // Send LS table
    }
    return 0;
}

int RouteNode::Stop() {
    running_ = false;
    return 0;
}

int RouteNode::SetRouteAlgoType(RouteAlgoType t) {
    if (t == algo_type_) return;
    route_algo_ = nullptr;
    switch
        t {
            case RouteAlgoType::LS:
                route_algo_ = make_unique<RouteLS>();
                break;
            case RouteAlgoType::DV:
                route_algo_ = make_unique<RouteDV>();
                break;
        }
    algo_type_ = t;
    return 0;
}

int RouteNode::SetActionMode(ActionMode am) {
    if (am == action_mode_) return;
    action_mode_ = am;
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