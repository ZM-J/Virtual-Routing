#include "route_ls.h"
#include "route_message.cpp"

#include <queue>
#include <string>

using namespace std;

std::vector<int> RouteLS::JudgePath(int from, int dest) {
    // judge the path by the route_table_
    // from to dest
    // may need to get the ips from args.h
    auto args_instance = Args::GetInstance();
}

int RouteLS::UpdateRouteMsg(const std::string& raw_msg_str) {
    LSAdvertisement ls_msg(raw_msg_str);
    // do something like the following
    // check others_advertisements_, if comes a seq_number, update it and
    //      broadcast this datagram to neighbor
    // the broadcast datagram will be push() into msg_to_send_
    //                                   (a thread_safe queue)
    route_table_;
    others_advertisements_;
    msg_to_send_;
    return 0;
}

queue<pair<string, string>> RouteLS::GenerateRouteMsg() {
    // pair.first is dest_ip
    // pair.second is the message

    // Generate all the Route Message that will be sent to others in one period
}