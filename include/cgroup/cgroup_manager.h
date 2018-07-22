#ifndef LXM_CGROUP_MANAGER_H
#define LXM_CGROUP_MANAGER_H
#include <string>
#include <map>
#include <memory>
#include "res_handler.h"

namespace LXM {
using std::string;
using std::map;
using std::shared_ptr;
class CGroupManager {
public:
    int init();
    void request(const string & res_name, float value);
    int apply(int pid);
    static void register_handler(const string &res_name, shared_ptr<ResHandler> handler);

private:
    string name;
    map<string, float> cgroup_res;
    static map<string, shared_ptr<ResHandler>> cgroup_res_handlers;
};
}

#endif