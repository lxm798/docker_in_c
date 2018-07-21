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
    void request(const string & res_name, float value);
    void apply(int pid);
    void register_handler(const string &res_name, shared_ptr<ResHandler> handler);

private:
    map<string, float> cgroup_res;
    map<string, shared_ptr<ResHandler>> cgroup_res_handlers;
};
}

#endif