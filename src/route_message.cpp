#include "route_message.h"

#include <cstdio>
#include <sstream>
#include <string>


using namespace std;

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
