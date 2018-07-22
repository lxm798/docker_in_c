#ifndef LXM_CGROUP_CPUHANDLER_H
#define LXM_CGROUP_CPUHANDLER_H
#include "cgroup/res_handler.h"
#include <string>
using std::string;
namespace LXM {
class CpuHandler : public ResHandler {
public:
    int init(const string &name);
    int apply(int pid, float v);
    ~CpuHandler() {};
private:
    string dir;
    int pid;
};
}
#endif
