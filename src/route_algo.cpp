#include "route_algo.h"
#include "route_message.h"

#include <string>
#include <vector>

using namespace std;

int RouteAlgo::UpdateConnectivity(const std::string& raw_msg_str) {
    ReachabilityMessage r_msg(raw_msg_str);
    // update the connectivity_table_
    // ..
    return 0;
}