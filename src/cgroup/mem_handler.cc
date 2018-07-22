#include "cgroup/mem_handler.h"
namespace LXM {
int MemHandler::init(const string &name) {
    dir = "/sys/fs/cgroup/memory/" + name;
    return create_dir_if_not_exist(dir);
}

int MemHandler::apply(int pid, float v) {
    if (append_to_file(dir + "/tasks", pid) < 0) {
        return -1;
    }
    if (write_to_file(dir + "/memory.limit_in_bytes", int(v * 1024 * 1024)) < 0) {
        return -1;
    }
    return 0;
}
}