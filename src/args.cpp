#include "args.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

std::shared_ptr<Args> Args::m_args = nullptr;

Args::Args() {
    nodes_number_ = 5;
    member_ips_[0] = "11.11.11.11";
    member_ips_[1] = "22.22.22.22";
    member_ips_[2] = "33.33.33.33";
    member_ips_[3] = "44.44.44.44";
    member_ips_[4] = "55.55.55.55";

    init_topo_table_ = std::vector<std::vector<int>>(5, std::vector<int>(5, 0));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) init_topo_table_[i][j] = 99999;
    }
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