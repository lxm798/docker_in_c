#ifndef LXM_CGROUP_MEM_HANDLER_H
#define LXM_CGROUP_MEM_HANDLER_H
#include "cgroup/res_handler.h"
#include <string>
using std::string;
namespace LXM {
class MemHandler : public ResHandler {
public:
    int init(const string &name);
    int apply(int pid, float v);
    ~MemHandler() {};
private:
    string dir;
    int pid;
};
}
#endif
