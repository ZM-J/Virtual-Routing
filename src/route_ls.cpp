#include "route_ls.h"
#include "route_message.cpp"

#include <queue>
#include <string>
#include <cstring>
#include <utility>

using namespace std;

// init DV.
// init route table.
RouteLS::RouteLS(const int node) : node_(node) {
	default_rote_ = -1;
	auto args = Args::GetInstance();
	auto dv = args->GetInterfaces(node_);

	for (std::size_t i = 0; i < dv.size(); i++)
		if (i != node_ && dv[i] != UNREACHABLE) {
			graph_.AddEdge(node_, i, dv[i]);
			dv_.push_back(std::make_pair(args->GetIp(i), dv[i]));
			route_table_[i] = i;
		} else {
			route_table_[i] = default_rote_;
		}
	route_table_[node_] = node_;
}
RouteLS::RouteLS(const std::string& ip) : node_(Args::GetInstance()->GetNode(ip)) {
	default_rote_ = -1;
	auto args = Args::GetInstance();
	auto dv = args->GetInterfaces(node_);

	for (std::size_t i = 0; i < dv.size(); i++)
		if (i != node_ && dv[i] != UNREACHABLE) {
			graph_.AddEdge(node_, i, dv[i]);
			dv_.push_back(std::make_pair(args->GetIp(i), dv[i]));
			route_table_[i] = i;
		} else {
			route_table_[i] = default_rote_;
		}
	route_table_[node_] = node_;
}

int RouteLS::GetNextHop(const std::size_t dest) const {
	return dest < route_table_.size() ? route_table_[dest] : default_rote_;
}

std::vector<int> RouteLS::JudgePath(int from, int dest) {
	// judge the path by the route_table_
	// from to dest
	// may need to get the ips from args.h
	auto args_instance = Args::GetInstance();
}

int RouteLS::UpdateRouteMsg(const std::string& raw_msg_str) {
	auto args = Args::GetInstance();
	LSAdvertisement msg(raw_msg_str);
	int from = args->GetNode(msg.generated_from_ip);
	for (const auto& n : msg.dv)
		graph_.AddEdge(from, args->GetNode(n.first), n.second);
	graph_.Dijkstra(node_);

	return 0;
}

queue<pair<string, string>> RouteLS::GenerateRouteMsg() {
	// pair.first is dest_ip
	// pair.second is the message

	// Generate all the Route Message that will be sent to others in one period
	auto args = Args::GetInstance();
	DVAdvertisement ad;
	ad.dv.reserve(dv_.size());
	ad.generated_from_ip = args->GetIp(node_);
	for (const auto& n : dv_)
		ad.dv.push_back(std::make_pair(n.first, (DVAdvertisement::CostFile)n.second));
	std::string ad_str(ad.GetSerializedMsg());
	for (const auto& n : dv_)
		msg_to_send_.push(std::make_pair(n.first, ad_str));
}
