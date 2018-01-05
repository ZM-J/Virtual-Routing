// NormalNode : Exchange route information to each-other
#ifndef VIRTUAL_ROUTING_ROUTE_NODE
#define VIRTUAL_ROUTING_ROUTE_NODE

#include "./args.h"
#include "./route_algo.h"
#include "./route_message.h"
#include "./socket_receiver.h"
#include "./socket_sender.h"
#include "./thread_safe_queue.h"

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
    int Start(int);
    int Stop();

    int SetRouteAlgoType(RouteAlgoType);
    int SetActionMode(ActionMode);

   protected:
    // RouteAlgoType : cannot Start() if not set
    RouteAlgoType algo_type_;
    std::unique_ptr<RouteAlgo> route_algo_;
    // ActionMode : cannot Start() if not set
    ActionMode action_mode_;

   private:
    bool running_;
    std::thread th_send_msg_;
    std::thread th_recv_msg_;
    std::thread th_hb_msg_;
    std::thread th_commands_;
    std::map<std::string, ReachabilityEnum> connectivity_;

    SocketSender sender_;
    SocketReceiver receiver_;
    //Queue<std::pair<std::string, std::string>> send_msg_queue_;
    int StartSendMsg();
    int StartRecvMsg();

    int WaitForCommands();

    // some commands, not determined. feel free to modify :P
    int AddDirectConnection(std::initializer_list<int>);
    int DeleteDirectConnection(std::initializer_list<int>);
    int JoinTopo();
    int LeaveTopo();
};

#endif