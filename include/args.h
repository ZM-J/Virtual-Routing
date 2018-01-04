// Args : Use SingleInstance
#ifndef VIRTUAL_ROUTING_ARGS
#define VIRTUAL_ROUTING_ARGS

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Args {
   public:
    ~Args();
    static std::shared_ptr<Args> GetInstance(void);
    int GetNodeNumber(void) const;
	int GetNode(const std::string&) const;
	std::string GetIp(const int) const;
	std::vector<int> GetInterfaces(const int) const;
	std::vector<int> GetInterfaces(const std::string&) const;



	typedef int CostType;
	typedef std::vector<CostType> DV;
	static const CostType INFINITE;

   protected:
    // Total Number of Nodes
    int nodes_number_;
    // store the initial topo table.
    std::vector<DV> init_topo_table_;
    std::map<int, std::string> member_ips_;

	std::unordered_map<std::string, int> ip_to_node_;

   private:
    Args();
    static std::shared_ptr<Args> m_args;
};

enum class RouteAlgoType { NONE, LS, DV };
enum class ActionMode { NONE, NORMAL, CLIENT, CONTROLLER };

#endif
