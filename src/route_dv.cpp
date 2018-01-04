#include "route_dv.h"
#include "route_message.cpp"

#include <queue>
#include <string>
#include <cstring>
#include <utility>

using namespace std;

// init DV.
// init route table.
RouteDV::RouteDV(const int node) : node_(node), cost_(Args::GetInstance()->GetInterfaces(node)),
	dv_(Args::GetInstance()->GetNodeNumber(), DV(Args::GetInstance()->GetNodeNumber(), UNREACHABLE)) {
	default_rote_ = -1;
	dv_[node_] = cost_;
	for (std::size_t i = 0; i < cost_.size(); i++)
		route_table_[i] = cost_[i] == UNREACHABLE ? default_rote_ : i;
}
RouteDV::RouteDV(const std::string& ip) : node_(Args::GetInstance()->GetNode(ip)),
    cost_(Args::GetInstance()->GetInterfaces(node_)),
    dv_(Args::GetInstance()->GetNodeNumber() - 1U, DV(Args::GetInstance()->GetNodeNumber(), UNREACHABLE)) {
	default_rote_ = -1;
	for (std::size_t i = 0; i < cost_.size(); i++)
		route_table_[i] = cost_[i] == UNREACHABLE ? default_rote_ : i;
}

int RouteDV::GetNextHop(const std::size_t dest) const {
	return dest < route_table_.size()? route_table_[dest] : default_rote_;
}

std::vector<int> RouteDV::JudgePath(int from, int dest) {
    // judge the path by the route_table_
    // from to dest
    // may need to get the ips from args.h
    auto args_instance = Args::GetInstance();
}

int RouteDV::UpdateRouteMsg(const std::string& raw_msg_str) {
	auto args = Args::GetInstance();
    DVAdvertisement msg(raw_msg_str);
	int from = args->GetNode(msg.generated_from_ip);
	for (const auto& n : msg.dv)
		dv_[from][args->GetNode(n.first)] = n.second;

	std::size_t n = dv_.size();
	bool dirty = false;
	for (std::size_t y = 0; y < n; y++) {
		dv_[node_][y] = UNREACHABLE;
		for (std::size_t v = 0; v < n; v++) {
			if (cost_[v] + dv_[v][y] < dv_[node_][y]) {
				dv_[node_][y] = cost_[v] + dv_[v][y];
				dirty = true;
				route_table_[y] = v;
			}
		}
	}

	if (dirty)
		GenerateRouteMsg();
    return 0;
}

queue<pair<string, string>> RouteDV::GenerateRouteMsg() {
    // pair.first is dest_ip
    // pair.second is the message

    // Generate all the Route Message that will be sent to others in one period
	auto args = Args::GetInstance();
	DVAdvertisement ad;
	ad.dv.reserve(cost_.size());
	ad.generated_from_ip = args->GetIp(node_);
	for (std::size_t i = 0; i < cost_.size(); i++)
		ad.dv.push_back(std::make_pair(args->GetIp(i), (DVAdvertisement::CostFile)cost_[i]));
	std::string ad_str(ad.GetSerializedMsg());
	for (std::size_t i = 0; i < cost_.size(); i++)
		if (cost_[i] != UNREACHABLE && i != static_cast<std::size_t>(node_))
			msg_to_send_.push(std::make_pair(args->GetIp(i), ad_str));
}
