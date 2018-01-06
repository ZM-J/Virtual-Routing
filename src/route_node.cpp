#include "route_node.h"
#include "args.h"
#include "route_dv.h"
#include "route_ls.h"

#include <functional>
#include <initializer_list>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

RouteNode::RouteNode() {
    algo_type_ = RouteAlgoType::NONE;
    action_mode_ = ActionMode::NONE;
    running_ = false;
}

RouteNode::~RouteNode() {
    // release the memory of RouteAlgo
    route_algo_ = nullptr;
}

int RouteNode::StartSendMsg() {
    std::pair<std::string, std::string> msg;
    while (running_) {
        /* Send Message code
        auto msg_send = send_msg_queue_.pop();
        string dest_ip = msg_send.first;
        string msg = msg_send.second;
        sender_.Send(dest_ip, msg);
        */
        switch (action_mode_) {
            case ActionMode::NONE:
                cout << "ActionMode MUST NOT BE NONE" << endl;
                exit(1);
                break;
            case ActionMode::NORMAL:
                msg = route_algo_->Send();
                sender_.Send(msg.first, msg.second);
                break;
            case ActionMode::CLIENT:
                msg = route_algo_->Send();
                sender_.Send(msg.first, msg.second);
                break;
            case ActionMode::CONTROLLER:
                break;
        }
    }
    return 0;
}

int RouteNode::StartRecvMsg() {
    auto reachability_response = [&](std::string r_msg) -> int {
        //r_msg;
        return 0;
    };
    auto process_LS = [&](std::string msg) -> int {
        route_algo_->UpdateRouteMsg(msg);
        return 0;
    };
    auto process_DV = [&](std::string msg) -> int {
        route_algo_->UpdateRouteMsg(msg);
        return 0;
    };
    receiver_.ListenAndReceive(reachability_response, process_LS, process_DV);
    return 0;
}

int RouteNode::WaitForCommands() {
    while (running_) {
        // Wait for stdinput
    }
    return 0;
}

int RouteNode::Start(int node) {
    bool check_ok = true;
    if (algo_type_ == RouteAlgoType::NONE) {
        check_ok = false;
        cout << "Routing Algorithm hasn\'t been specified. (LS, DV)" << endl;
    }
    if (action_mode_ == ActionMode::NONE) {
        check_ok = false;
        cout << "Action Mode hasn\'t been specified. (NORMAL, CLIENT, "
                "CONTROLLER)"
             << endl;
    }
    if (!check_ok) return 1;
    route_algo_->SetNode(node);
    running_ = true;
    th_send_msg_ = std::thread([&] { StartSendMsg(); });
    th_recv_msg_ = std::thread([&] { StartRecvMsg(); });
    th_commands_ = std::thread([&] { WaitForCommands(); });
    th_hb_msg_ = std::thread([&] {
        while (running_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(RouteAlgo::PERIOD) / 5 * 1000));
            route_algo_->CheckNode();
        }
    });
    return 0;
}

int RouteNode::Stop() {
    running_ = false;
    th_send_msg_.join();
    th_recv_msg_.join();
    th_commands_.join();
    th_hb_msg_.join();
    return 0;
}

int RouteNode::SetRouteAlgoType(RouteAlgoType t) {
    if (t == algo_type_) return 0;
    route_algo_ = nullptr;
    switch (t) {
        case RouteAlgoType::LS:
            route_algo_ = make_unique<RouteLS>();
            break;
        case RouteAlgoType::DV:
            route_algo_ = make_unique<RouteDV>();
            break;
        case RouteAlgoType::NONE:
            break;
    }
    algo_type_ = t;
    return 0;
}

int RouteNode::SetActionMode(ActionMode am) {
    if (am == action_mode_) return 0;
    action_mode_ = am;
    return 0;
}

// Specific commands
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