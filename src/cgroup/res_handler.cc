#include "cgroup/res_handler.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace LXM {
bool ResHandler::is_dir_exist(const string & dir_path) {
    int ret = access(dir_path.c_str(), F_OK);
    return ret == 0;
}
int ResHandler::create_dir_if_not_exist(const string & dir_path) {
    if (!is_dir_exist(dir_path)) {
        if (mkdir(dir_path.c_str(), 0775) < 0) {
            perror(("mkdir " + dir_path).c_str());
            return -1;
        }
    }
    return 0;
}
}