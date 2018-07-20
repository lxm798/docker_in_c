#include "flags.h"
#include "ns/name_space_manager.h"
#include <memory>
#include <unistd.h>
#include <sched.h>
#define STACK_SIZE (1024 * 1024)
using std::shared_ptr;
using LXM::NsManager;

int main_process(void * arg) {
    int fd = (int) arg;
    shared_ptr<NsManager> ns_manager = std::make_shared<NsManager>(new NsManager());
    ns_manager.init();
    ns_manager.mount();
    
    ns_manager.exec();
}
int main (int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int fds[2];
    int ret = pipe(fds);
    if (ret < 0) {
        return -1;
    }
    char * stack = (char *) malloc(STACK_SIZE); 
    int pid = clone(main_process, stack + STACK_SIZE,);
    return 0;
}