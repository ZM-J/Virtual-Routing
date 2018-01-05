#include "route_node.h"
#include "args.h"
#include <string>
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    //if (argc < 2) {
    //    throw;
    //}
    RouteNode node;
    node.SetActionMode(ActionMode::NORMAL);
    node.SetRouteAlgoType(RouteAlgoType::LS);
    //node.Start(std::stoi(argv[1]));
    node.Start(0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    node.Stop();
    return 0;
}
