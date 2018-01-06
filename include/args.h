// Args : Use SingleInstance
#ifndef VIRTUAL_ROUTING_ARGS
#define VIRTUAL_ROUTING_ARGS

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Args {
   public:

    typedef int CostType;
    typedef int NodeType;
    typedef std::string IpType;
    typedef std::vector<CostType> DV;
    static const CostType INFINITE;

    ~Args();
    static std::shared_ptr<Args> GetInstance(void);

    std::size_t GetNodeNumber(void) const;
    NodeType GetNode(const IpType&) const;
    IpType GetIp(const NodeType) const;
    DV GetInterfaces(const NodeType) const;
    DV GetInterfaces(const IpType&) const;

   protected:
    // Total Number of Nodes
    std::size_t nodes_number_;
    // store the initial topo table.
    std::vector<DV> init_topo_table_;

    std::vector<IpType> node_to_ip_;
    std::unordered_map<IpType, NodeType> ip_to_node_;

   private:
    Args();
    static std::shared_ptr<Args> m_args;
};

enum class RouteAlgoType { NONE, LS, DV };
enum class ActionMode { NONE, NORMAL, CLIENT, CONTROLLER };

#endif
