// base class for different routing algorithm
#ifndef VIRTUAL_ROUTING_ROUTE_ALGO
#define VIRTUAL_ROUTING_ROUTE_ALGO

#include "./args.h"
#include "./thread_safe_queue.h"

#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include <mutex>

class RouteAlgo {
   public:

    typedef Args::CostType CostType;
    typedef Args::NodeType NodeType;
    typedef Args::IpType IpType;
    typedef Args::DV DV;

    static const CostType UNREACHABLE;
    static const double PERIOD;
 
    typedef struct Timer {
        std::vector<std::time_t> time_;
        std::mutex tm_;

        void SetTime(std::size_t node, std::time_t time = std::time(0)) {
            std::lock_guard<std::mutex> guard(tm_);
            if (node >= time_.size())
                time_.resize(node + 1U, 0);
            time_[node] = time;
        }

        std::vector<NodeType> CheckTime(void) {
            std::vector<NodeType> dirty;
            std::lock_guard<std::mutex> guard(tm_);
            for (std::size_t i = 0; i < time_.size(); i++)
                if (time_[i] && std::difftime(std::time(0), time_[i]) > PERIOD) {
                    time_[i] = 0;
                    dirty.push_back(i);
                }
            return dirty;
        }
    } Timer;
    typedef struct Interfaces {
        DV dv_;
        std::mutex tm_;

        DV Get(void) {
            std::lock_guard<std::mutex> guard(tm_);
            return dv_;
        }

        void Set(const DV& ot) {
            std::lock_guard<std::mutex> guard(tm_);
            dv_ = ot;
        }

        void Set(std::size_t node, CostType cost) {
            std::lock_guard<std::mutex> guard(tm_);
            if (node >= dv_.size())
                dv_.resize(node + 1U, 0);
            dv_[node] = cost;
        }

        void Del(std::size_t node) {
            std::lock_guard<std::mutex> guard(tm_);
            if (node >= dv_.size())
                dv_.resize(node + 1U, 0);
            dv_[node] = UNREACHABLE;
        }
    } Interfaces;

    RouteAlgo() = default;
    ~RouteAlgo() = default;

    virtual int UpdateRouteMsg(const std::string&) = 0;
    // GenereateRouteMsg is to Genereate route msg by itself
    virtual void GenerateRouteMsg() = 0;

    virtual void SetNode(const NodeType) = 0;
    virtual void CheckNode(void) = 0;

    IpType GetNextHop(const std::size_t) const;
    std::pair<std::string, std::string> Send(void);

   protected:
    std::vector<NodeType> route_table_;
    Queue<std::pair<std::string, std::string>> msg_to_send_;

    NodeType node_;
    NodeType default_route_;
    Timer recv_time_;
    Interfaces intfes_;
};

#endif
