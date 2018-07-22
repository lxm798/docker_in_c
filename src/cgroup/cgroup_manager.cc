#include "cgroup/cgroup_manager.h"
namespace LXM {
int CGroupManager::init() {
    name.assign("lxm");
    for (auto & v : cgroup_res_handlers) {
        if (v.second->init(name) < 0) {
            perror(v.first.c_str());
            return -1;
        }
    }
    return 0;
}
void CGroupManager::request(const string & res_name, float value) {
    cgroup_res[res_name] = value;
}

int CGroupManager::apply(int pid) {
    for (auto res : cgroup_res) {
        shared_ptr<ResHandler> handler = cgroup_res_handlers[res.first];
        if (handler->apply(pid, res.second) < 0) {
            return -1;
        }
    }
    return 0;
}

void CGroupManager::register_handler(const string &res_name, shared_ptr<ResHandler> handler) {
    cgroup_res_handlers[res_name] = handler;
}

map<string, shared_ptr<ResHandler>> CGroupManager::cgroup_res_handlers;
}