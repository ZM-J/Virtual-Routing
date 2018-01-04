#include "route_message.h"

#include <cstdio>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstring>

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

struct LSAdvertisement {
	static const unsigned int IPLEN = 16;
	typedef int8_t CostFile;
	typedef char IpFile[IPLEN];

	typedef std::pair<std::string, CostFile> info;
	std::string generated_from_ip;
	std::vector<info> dv;

	static_assert(sizeof(CostFile) == 1U, "For Endianness.");
	LSAdvertisement() = default;
	LSAdvertisement(const std::string& raw_msg_str) {
		const char* data = raw_msg_str.c_str() + 1U;
		const char* end = data + raw_msg_str.size();
		generated_from_ip = data;
		for (data += IPLEN; data < end; data += IPLEN + sizeof(CostFile)) {
			dv.push_back(info(data, *(CostFile*)(data + IPLEN)));
		}
	}
	std::string GetSerializedMsg() {
		std::size_t len = IPLEN * dv.size() + IPLEN + 2U;
		std::unique_ptr<char> msg(new char[len]);
		char* data = msg.get();
		*data = 'L';
		data += 1U;
		std::memcpy(data, generated_from_ip.c_str(), generated_from_ip.size());
		data += IPLEN;
		for (const auto& n : dv) {
			std::memcpy(data, n.first.c_str(), n.first.size());
			*(CostFile*)(data + IPLEN) = n.second;
			data += IPLEN + sizeof(CostFile);
		}
		return msg.get();
	}
};


struct DVAdvertisement {
	static const unsigned int IPLEN = 16;
    typedef int8_t CostFile;
    typedef char IpFile[IPLEN];

	typedef std::pair<std::string, CostFile> info;
    std::string generated_from_ip;
    std::vector<info> dv;

    static_assert(sizeof(CostFile) == 1U, "For Endianness.");
    DVAdvertisement() = default;
    DVAdvertisement(const std::string& raw_msg_str) {
		const char* data = raw_msg_str.c_str() + 1U;
		const char* end = data + raw_msg_str.size();
		generated_from_ip = data;
		for (data += IPLEN; data < end; data += IPLEN + sizeof(CostFile)) {
			dv.push_back(info(data, *(CostFile*)(data + IPLEN)));
		}
    }
	std::string GetSerializedMsg() {
		std::size_t len = IPLEN * dv.size() + IPLEN + 2U;
		std::unique_ptr<char> msg(new char[len]);
		char* data = msg.get();
		*data = 'D';
		data += 1U;
		std::memcpy(data, generated_from_ip.c_str(), generated_from_ip.size());
		data += IPLEN;
		for (const auto& n : dv) {
			std::memcpy(data, n.first.c_str(), n.first.size());
			*(CostFile*)(data + IPLEN) = n.second;
			data += IPLEN + sizeof(CostFile);
		}
		return msg.get();
	}
};
