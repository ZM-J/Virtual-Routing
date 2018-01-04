// Routing-Algorithm : Link-State
#ifndef VIRTUAL_ROUTING_ROUTE_LS
#define VIRTUAL_ROUTING_ROUTE_LS

#include "./route_algo.h"
#include "./route_message.h"

#include <map>
#include <queue>
#include <string>
#include <utility>

class RouteLS : public RouteAlgo {
   public:

	typedef struct Graph {
		std::vector<std::vector<int>> cost;

		Graph() = default;

		void AddEdge(int from, int dest, int weight) {
			int n = std::max(from, dest) + 1;
			if (n > cost.size()) {
				for (std::size_t i = 0; i < cost.size(); i++)
					cost[i].resize(n, UNREACHABLE);
				cost.resize(n, std::vector<int>(n, UNREACHABLE));
			}
			cost[from][dest] = weight;
		}
		void DelNode(int node) {
			if (node < cost.size()) {
				for (std::size_t i = 0; i < cost.size(); i++)
					cost[node][i] = cost[i][node] = UNREACHABLE;
			}
		}

		std::vector<int> Dijkstra(const int source) {
			std::vector<int> prev(cost.size(), UNREACHABLE);
			prev[source] = source;
			std::vector<bool> visited(cost.size(), false);
			std::vector<int> dis(cost.size(), UNREACHABLE);
			dis[source] = 0;

			do {
				int min = UNREACHABLE, pos = -1;
				for (std::size_t j = 0; j < cost.size(); ++j) {
					if (!visited[j] && dis[j] < min) {
						min = dis[j];
						pos = j;
					}
				}
				if (pos == -1)
					break;
				visited[pos] = true;
				for (std::size_t v = 0; v < cost.size(); ++v) {
					if (!visited[v] && dis[pos] + cost[pos][v] < dis[v]) {
						dis[v] = dis[pos] + cost[pos][v];
						prev[v] = pos == source ? v : prev[pos];
					}
				}
			} while (1);
			return prev;
		}
	} Graph;

	RouteLS(const int);
	RouteLS(const std::string&);
	vector<int> JudgePath(int, int);
	int UpdateRouteMsg(const std::string&);
	queue<pair<string, string>> GenerateRouteMsg();
	int GetNextHop(const std::size_t) const;

	// more funcs ...

   private:
	map<string, DVAdvertisement> others_advertisements_;

	typedef std::pair<std::string, Args::CostType> info;
	typedef std::vector<info> DV;
	int node_;
	Graph graph_;
	DV dv_;

    // Queue<pair<string, string>> msg_to_send_; inherited from RouteAlgo
};

#endif
