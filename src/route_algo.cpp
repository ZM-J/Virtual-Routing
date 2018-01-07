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

void RouteAlgo::RoutePrint(void) const {
    std::fprintf(stdout, "________________________________________%s________________________________________\n", "Route Table");
    auto args = Args::GetInstance();
    for (std::size_t i = 0; i < route_table_.size(); i++)
        std::fprintf(stdout, "%18s", args->GetIp(i).c_str());
    std::fprintf(stdout, "\n");
    for (std::size_t i = 0; i < route_table_.size(); i++) {
        if (route_table_[i] != UNREACHABLE)
            std::fprintf(stdout, "%18d", route_table_[i]);
        else
            std::fprintf(stdout, "%18s", "UNREACHABLE");
    }
    std::fprintf(stdout, "\n");
}
