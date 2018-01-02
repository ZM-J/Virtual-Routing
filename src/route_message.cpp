#include "route_message.h"

#include <cstdio>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct ReachabilityMessage {
    std::string from_ip;
    std::string dest_ip;
    ReachabilityEnum check_flag;

    ReachabilityMessage() = default;
    ReachabilityMessage(const std::string& raw_msg_str) {
        string::size_type ip_sep_pos = raw_msg_str.find(',');
        string::size_type chk_sep_pos = raw_msg_str.find('|');
        // Remember to ignore the "R" Header (substr() start with index 1)
        from_ip = raw_msg_str.substr(1, ip_sep_pos);
        dest_ip =
            raw_msg_str.substr(ip_sep_pos + 1, chk_sep_pos - ip_sep_pos - 1);
        check_flag = static_cast<ReachabilityEnum>(
            stoi(raw_msg_str.substr(chk_sep_pos + 1)));
    }

    std::string GetSerializedMsg() {
        const char* fip = from_ip.c_str();
        const char* dip = dest_ip.c_str();
        char msg_cstr[40];
        // Reachability Message Header: Started with a single "R"
        sprintf(msg_cstr, "R%s,%s|%d", fip, dip, static_cast<int>(check_flag));
        return std::string(msg_cstr);
    }
};

struct LSAdvertisement {
    std::string generated_from_ip;
    int seq_number;  // increases by 1 every time the source node generates a
                     // new datagram.
    std::vector<std::string> neighbor_ips;

    LSAdvertisement() = default;
    LSAdvertisement(const std::string& raw_msg_str) {
        string::size_type pos_gen_ip_end = raw_msg_str.find('|');
        string::size_type pos_seq_num_end = raw_msg_str.find(';');
        // Remember to ignore the "L" Header (substr() start with index 1)
        generated_from_ip = raw_msg_str.substr(1, pos_gen_ip_end);
        seq_number = stoi(raw_msg_str.substr(
            pos_gen_ip_end + 1, pos_seq_num_end - pos_gen_ip_end - 1));

        string::size_type pos_last_neighbor_ip_sep = pos_seq_num_end;
        string::size_type pos_cur_neighbor_ip_sep;
        // will automatically check if the neighbor_ips field exists
        // string.find will also return a string::npos when start_pos is
        //      out_of_range
        while ((pos_cur_neighbor_ip_sep = raw_msg_str.find(
                    ',', pos_last_neighbor_ip_sep + 1)) != string::npos) {
            string cur_ip_neighbor = raw_msg_str.substr(
                pos_last_neighbor_ip_sep + 1,
                pos_cur_neighbor_ip_sep - pos_last_neighbor_ip_sep - 1);
            neighbor_ips.push_back(std::move(cur_ip_neighbor));
            pos_last_neighbor_ip_sep = pos_cur_neighbor_ip_sep;
        }
    }

    std::string GetSerializedMsg() {
        std::ostringstream ostrs;
        // LS datagram Header: Start with a single "L"
        ostrs << "L";
        ostrs << generated_from_ip << "|";
        ostrs << seq_number << ";";
        for (auto& ip : neighbor_ips) {
            ostrs << ip << ",";
        }
        return ostrs.str();
    }
};

struct DVAdvertisement {
    // not determined yet, feel free to modify

    DVAdvertisement() = default;
    DVAdvertisement(const std::string& raw_msg_str) {
        // ..
    }
    std::string GetSerializedMsg() {
        // ..
        return "";
    }
};