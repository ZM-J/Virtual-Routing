#include "RouteLS.hpp"

#include <string>

using namespace std;

int RouteLS::SendRouteMsg(string msg, string dest) {
    int errno = 0;
    return errno;
}

int RouteLS::RecvRouteMsg(string msgGet) {
    int errno = 0;
    return errno;
}

string RouteLS::serializeMsg(std::vector<std::vector<int> >& table) {
    string ret;
    return ret;
}
std::vector<std::vector<int> > RouteLS::parseMsg(string msg) {
    std::vector<std::vector<int> > ret;
    return ret;
}