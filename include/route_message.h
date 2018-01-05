#ifndef ROUTE_MESSAGE
#define ROUTE_MESSAGE

#include <sstream>
#include <memory>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

/**
 * Reachability protocol Msg
 * from_ip, dest_ip
 * check_flag :
 */
enum class ReachabilityEnum { kCheckConnect, kConnectOK, kDisconnected };

template <typename T>
std::ostream& operator<<(
    typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream,
    const T& e) {
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

struct ReachabilityMessage;


struct LSAdvertisement {
    static const unsigned int IPLEN = 16;
    typedef int CostFile;
    typedef char IpFile[IPLEN];

    typedef std::pair<std::string, CostFile> info;
    std::string generated_from_ip;
    std::vector<info> dv;

    LSAdvertisement() = default;
    LSAdvertisement(const std::string& raw_msg_str) {
        const char* data = raw_msg_str.data() + 1U;
        const char* end = raw_msg_str.data() + raw_msg_str.size();
        generated_from_ip = data;
        for (data += IPLEN; data < end; data += IPLEN + sizeof(CostFile)) {
            const char* p = data + IPLEN;
            CostFile tmp = 0;
            for (std::size_t i = 0; i < sizeof(CostFile); i++) {
                tmp = (tmp << 8U) | p[i];
            }
            dv.push_back(info(data, tmp));
        }
    }
    std::string GetSerializedMsg() {
        std::size_t len = (IPLEN + sizeof(CostFile)) * dv.size() + IPLEN + 1U;
        std::unique_ptr<char> msg(new char[len]);
        char* data = msg.get();
        *data = 'D';
        data += 1U;
        std::memcpy(data, generated_from_ip.c_str(), generated_from_ip.size() + 1U);
        data += IPLEN;
        for (const auto& n : dv) {
            std::memcpy(data, n.first.c_str(), n.first.size() + 1U);
            data += IPLEN;
            for (std::size_t i = sizeof(CostFile) * 8U; i; data++) {
                i -= 8U;
                *data = (n.second >> i) & 0xFF;
            }
        }
        return std::string(msg.get(), len);
    }
};

struct DVAdvertisement {
    static const unsigned int IPLEN = 16;
    typedef int CostFile;
    typedef char IpFile[IPLEN];

    typedef std::pair<std::string, CostFile> info;
    std::string generated_from_ip;
    std::vector<info> dv;

    DVAdvertisement() = default;
    DVAdvertisement(const std::string& raw_msg_str) {
        const char* data = raw_msg_str.data() + 1U;
        const char* end = raw_msg_str.data() + raw_msg_str.size();
        generated_from_ip = data;
        for (data += IPLEN; data < end; data += IPLEN + sizeof(CostFile)) {
            const char* p = data + IPLEN;
            CostFile tmp = 0;
            for (std::size_t i = 0; i < sizeof(CostFile); i++) {
                tmp = (tmp << 8U) | p[i];
            }
            dv.push_back(info(data, tmp));
        }
    }
    std::string GetSerializedMsg() {
        std::size_t len = (IPLEN + sizeof(CostFile)) * dv.size() + IPLEN + 1U;
        std::unique_ptr<char> msg(new char[len]);
        char* data = msg.get();
        *data = 'D';
        data += 1U;
        std::memcpy(data, generated_from_ip.c_str(), generated_from_ip.size() + 1U);
        data += IPLEN;
        for (const auto& n : dv) {
            std::memcpy(data, n.first.c_str(), n.first.size() + 1U);
            data += IPLEN;
            for (std::size_t i = sizeof(CostFile) * 8U; i; data++) {
                i -= 8U;
                *data = (n.second >> i) & 0xFF;
            }
        }
        return std::string(msg.get(), len);
    }
};


#endif
