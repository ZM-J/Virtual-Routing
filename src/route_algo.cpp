#include "route_algo.h"

const RouteAlgo::CostType RouteAlgo::UNREACHABLE = Args::INFINITE;
const double RouteAlgo::PERIOD = 5;

RouteAlgo::IpType RouteAlgo::GetNextHop(const std::size_t dest) const {
    NodeType out = dest < route_table_.size() ? route_table_[dest] : default_route_;
    return out == UNREACHABLE? "" : Args::GetInstance()->GetIp(out);
}

std::pair<std::string, std::string> RouteAlgo::Send(void) {
    return msg_to_send_.pop();
}
