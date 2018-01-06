// Routing-Algorithm : Link-State
#ifndef VIRTUAL_ROUTING_ROUTE_LS
#define VIRTUAL_ROUTING_ROUTE_LS

#include "./route_algo.h"

#include <string>
#include <vector>
#include <mutex>
#include <utility>

class RouteLS : public RouteAlgo {
   public:

    int UpdateRouteMsg(const std::string&);
    void GenerateRouteMsg();
    void SetNode(const NodeType);
    void CheckNode(void);

    typedef struct Graph {
        std::vector<std::vector<CostType>> cost;
        std::mutex tm_;

        Graph() = default;

        void AddEdge(NodeType from, NodeType dest, CostType weight) {
            std::size_t n = std::max(from, dest) + 1;
            std::lock_guard<std::mutex> guard(tm_);
            if (n > cost.size()) {
                for (std::size_t i = 0; i < cost.size(); i++)
                    cost[i].resize(n, UNREACHABLE);
                cost.resize(n, std::vector<CostType>(n, UNREACHABLE));
            }
            cost[dest][from] = cost[from][dest] = weight;
        }
        void DelNode(std::size_t node) {
            std::lock_guard<std::mutex> guard(tm_);
            if (node < cost.size()) {
                for (std::size_t i = 0; i < cost.size(); i++)
                    cost[node][i] = cost[i][node] = UNREACHABLE;
            }
        }
        NodeType GetCost(std::size_t from, std::size_t dest) {
            std::lock_guard<std::mutex> guard(tm_);
            return cost[from][dest];
        }
        std::vector<int> Dijkstra(const NodeType source) {
            std::vector<NodeType> prev(cost.size(), UNREACHABLE);
            prev[source] = source;
            std::vector<bool> visited(cost.size(), false);
            std::vector<CostType> dis(cost.size(), UNREACHABLE);
            dis[source] = 0;
            const std::size_t n = cost.size();
            std::lock_guard<std::mutex> guard(tm_);
            do {
                CostType min = UNREACHABLE;
                NodeType pos = -1;
                for (std::size_t j = 0; j < n; ++j) {
                    if (!visited[j] && dis[j] < min) {
                        min = dis[j];
                        pos = j;
                    }
                }
                if (pos == -1)
                    break;
                visited[pos] = true;
                for (std::size_t v = 0; v < n; ++v) {
                    if (!visited[v] && dis[pos] + cost[pos][v] < dis[v]) {
                        dis[v] = dis[pos] + cost[pos][v];
                        prev[v] = pos == source ? v : prev[pos];
                    }
                }
            } while (1);
            return prev;
        }

        void Print(void) {
            std::fprintf(stdout, "________________________________________%s________________________________________\n", "Graph");
            std::fprintf(stdout, "%18s", "");
            auto args = Args::GetInstance();
            for (std::size_t i = 0; i < cost.size(); i++)
                std::fprintf(stdout, "%18s", args->GetIp(i).c_str());
            for (std::size_t i = 0; i < cost.size(); i++) {
                std::fprintf(stdout, "\n%18s", args->GetIp(i).c_str());
                for (std::size_t j = 0; j < cost[i].size(); j++)
                    if (cost[i][j] != UNREACHABLE)
                        std::fprintf(stdout, "%18d", cost[i][j]);
                    else
                        std::fprintf(stdout, "%18s", "Inf");
            }
            std::fprintf(stdout, "\n");
        }
    } Graph;

   private:
    Graph graph_;
};

#endif
