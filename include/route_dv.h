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

        void Set(const std::size_t node, const DV& dv) {
            std::lock_guard<std::mutex> guard(tm_);
            dv_[node] = dv;
        }

        bool Update(const NodeType node_, const DV& cost, std::vector<NodeType>&route_table_) {
            bool dirty = false;
            std::lock_guard<std::mutex> guard(tm_);

            const std::size_t n = dv_.size();
            for (std::size_t y = 0; y < n; y++) {
                route_table_[y] = dv_[node_][y] = UNREACHABLE;
                for (std::size_t v = 0; v < n; v++) {
                    if (cost[v] + dv_[v][y] < dv_[node_][y]) {
                        dv_[node_][y] = cost[v] + dv_[v][y];
                        dirty = true;
                        route_table_[y] = v;
                    }
                }
            }
            return dirty;
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