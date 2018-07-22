#include "cgroup/cpu_handler.h"
namespace LXM {
int CpuHandler::init(const string &name) {
    dir = "/sys/fs/cgroup/cpu/" + name;
    return create_dir_if_not_exist(dir);
}
int CpuHandler::apply(int pid, float v) {
    if (append_to_file(dir + "/tasks", pid) < 0) {
        return -1;
    }
    if (write_to_file(dir + "/cpu.cfs_quota_us", int(v)) < 0) {
        return -1;
    }
    return 0;
}
}