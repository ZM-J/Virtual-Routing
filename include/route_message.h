#include <sstream>

using namespace std;

/**
 * Reachability protocol Msg
 * from_ip, dest_ip
 * check_flag :
 */
enum class ReachabilityEnum { SYN, ACK, RACK };
enum class ConnectionStatus { ESTABLISHED, DISCONNECTED };

template <typename T>
std::ostream& operator<<(
    typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream,
    const T& e) {
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

struct ReachabilityMessage;
struct LSAdvertisement;
