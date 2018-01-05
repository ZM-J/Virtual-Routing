#include "args.h"

#include <vector>

std::shared_ptr<Args> Args::m_args = nullptr;
const Args::CostType Args::INFINITE = 0x3f3f3f3f;

Args::Args() {
    nodes_number_ = 5;
    node_to_ip_.resize(nodes_number_);
    node_to_ip_[0] = "11.11.11.11";
    node_to_ip_[1] = "22.22.22.22";
    node_to_ip_[2] = "33.33.33.33";
    node_to_ip_[3] = "44.44.44.44";
    node_to_ip_[4] = "55.55.55.55";

	for (std::size_t i = 0; i < node_to_ip_.size(); i++)
		ip_to_node_[node_to_ip_[i]] = i;

    init_topo_table_ = std::vector<DV>(nodes_number_, DV(nodes_number_, INFINITE));

    for (std::size_t i = 0; i < init_topo_table_.size(); i++)
        init_topo_table_[i][i] = 0;

    init_topo_table_[0][2] = init_topo_table_[2][0] = 3;
    init_topo_table_[0][3] = init_topo_table_[3][0] = 4;
    init_topo_table_[0][4] = init_topo_table_[4][0] = 6;

    init_topo_table_[1][3] = init_topo_table_[3][1] = 2;
    init_topo_table_[1][4] = init_topo_table_[4][1] = 6;
    init_topo_table_[2][3] = init_topo_table_[3][2] = 8;
}
Args::~Args() { Args::m_args = nullptr; }

std::shared_ptr<Args> Args::GetInstance(void) {
    if (m_args == nullptr) m_args = std::shared_ptr<Args>(new Args());
    return m_args;
}

std::size_t Args::GetNodeNumber(void) const {
	return nodes_number_;
}

Args::NodeType Args::GetNode(const Args::IpType & ip) const {
	return ip_to_node_.at(ip);
}

Args::IpType Args::GetIp(const Args::NodeType node) const {
	return node_to_ip_.at(node);
}

Args::DV Args::GetInterfaces(const Args::IpType & ip) const {
	return init_topo_table_.at(ip_to_node_.at(ip));
}

Args::DV Args::GetInterfaces(const Args::NodeType node) const {
	return init_topo_table_.at(node);
}
