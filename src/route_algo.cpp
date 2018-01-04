#include "route_algo.h"
#include "./route_message.cpp"

#include <string>
#include <vector>

using namespace std;

const Args::CostType UNREACHABLE = Args::INFINITE;

int RouteAlgo::UpdateConnectivity(const std::string& raw_msg_str) {
    ReachabilityMessage r_msg(raw_msg_str);
    // update the connectivity_table_
    // ..
    return 0;
}

queue<pair<string, string>> RouteAlgo::GetOtherMsgToSend() {
    // ..
}