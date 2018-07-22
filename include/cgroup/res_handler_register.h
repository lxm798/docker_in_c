#ifndef LXM_RES_HANDLER_REGISTER_H
#define LXM_RES_HANDLER_REGISTER_H
#include "cgroup/cpu_handler.h"
#include "cgroup/mem_handler.h"
#include "cgroup/cgroup_manager.h"
#include <memory>
using std::make_shared;
namespace LXM {
class ResHandlerRegister {
public:
    ResHandlerRegister() {
        CGroupManager::register_handler("cpu", make_shared<CpuHandler>());
        CGroupManager::register_handler("mem", make_shared<MemHandler>());
    }
};
}
#endif