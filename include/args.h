// Args : Use SingleInstance

#include <map>
#include <string>
#include <vector>

class Args {
   public:
    ~Args();
    static std::shared_ptr<Args> GetInstance(void);

   protected:
    // Total Number of Nodes
    int nodes_number_;
    // store the initial topo table.
    std::vector<std::vector<int> > init_topo_table_;
    std::map<int, std::string> member_ips_;

   private:
    Args();
    static std::shared_ptr<Args> m_args;
};

enum RouteAlgoType { NONE_Algo, LS, DV };
enum ActionMode { NONE_Action, NORMAL, CLIENT, CONTROLLER };