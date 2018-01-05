// Routing-Algorithm : Distance-Vector
#ifndef VIRTUAL_ROUTING_ROUTE_DV
#define VIRTUAL_ROUTING_ROUTE_DV

#include "./route_algo.h"

#include <string>
#include <vector>
#include <mutex>

class RouteDV : public RouteAlgo {
   public:

    typedef struct DVTable{
        std::vector<DV> dv_;
        std::mutex tm_;

        void Init(const std::size_t n) {
            std::lock_guard<std::mutex> guard(tm_);
            dv_ = std::vector<DV>(n, DV(n, UNREACHABLE));
        }

        DV Get(const std::size_t node) {
            std::lock_guard<std::mutex> guard(tm_);
            return dv_[node];
        }

        void Set(const std::size_t node, const DV& dv) {
            std::lock_guard<std::mutex> guard(tm_);
            dv_[node] = dv;
        }
        void Set(const std::size_t from, const std::size_t dest, const NodeType cost) {
            std::lock_guard<std::mutex> guard(tm_);
            dv_[from][dest] = cost;
        }

        bool Update(const std::size_t node_, const DV& cost, std::vector<NodeType>&route_table_) {
            bool dirty = false;
            std::lock_guard<std::mutex> guard(tm_);

            const std::size_t n = dv_.size();
            for (std::size_t y = 0; y < n; y++) {
                if (y != node_) {
                    route_table_[y] = UNREACHABLE;
                    NodeType mc = UNREACHABLE;
                    for (std::size_t v = 0; v < n; v++) {
                        if (v != node_ && cost[v] + dv_[v][y] < mc) {
                            mc = cost[v] + dv_[v][y];
                            dirty = mc < dv_[node_][y];
                            route_table_[y] = v;
                        }
                    }
                    dv_[node_][y] = mc;
                }
            }
            return dirty;
        }

        void Print(void) {
            std::fprintf(stdout, "________________________________________%s________________________________________\n", "DV Table");
            std::fprintf(stdout, "%18s", "");
            auto args = Args::GetInstance();
            for (std::size_t i = 0; i < dv_.size(); i++)
                std::fprintf(stdout, "%18s", args->GetIp(i).c_str());
            for (std::size_t i = 0; i < dv_.size(); i++) {
                std::fprintf(stdout, "\n%18s", args->GetIp(i).c_str());
                for (std::size_t j = 0; j < dv_[i].size(); j++)
                    if (dv_[i][j] != UNREACHABLE)
                        std::fprintf(stdout, "%18d", dv_[i][j]);
                    else
                        std::fprintf(stdout, "%18s", "Inf");
            }
            std::fprintf(stdout, "\n");
        }
    } DVTable;

    int UpdateRouteMsg(const std::string&);
    void GenerateRouteMsg();
    void SetNode(const NodeType);
    void CheckNode(void);

   private:
    DVTable dv_;
};

#endif