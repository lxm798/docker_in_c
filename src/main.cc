#include "flags.h"
#include "ns/namespace_manager.h"
#include "cgroup/cgroup_manager.h"
#include <memory>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/capability.h>
#define STACK_SIZE (1024 * 1024)
using std::shared_ptr;
using LXM::NsManager;
    int fds[2];
void notify_close(int fd) {
    close(fd);
}
void wait_close(int fd) {
    char ch;
    read(fd, &ch, 1);
}
int set_map(char *path) {
    FILE * f = fopen(path, "w");
    FILE * f1 = fopen(path, "w");
    if (f == NULL) {
        perror("fopen");
        return -1;
    }
    printf("----------------fileno:%d", f->_fileno);
    if (fprintf(f, "%d %d %d", 0, 0, 65534) < 0) {
        printf("----------------fileno:%d  %d %s\n", f->_fileno, f1->_fileno , path);
        sleep(1);
        perror("fprintf");
        fclose(f);
        return -1;
    }
    if (fclose(f) < 0) {
        perror("fclose");
        return -1;
    }
    return 0;
}

int set_uid_and_gid(pid_t pid) {
    char path[1024];
    sprintf(path, "/proc/%d/uid_map", pid);
    set_map(path);
    sprintf(path, "/proc/%d/gid_map", pid);
    set_map(path);
    sprintf(path, "cat /proc/%d/uid_map", pid);
    system(path);
    printf("--------------------------------------%d %s", pid, path);
    return 0;
}
int main_process(void * arg) {
    // int *fds = (int *) arg;
    close(fds[1]);
    wait_close(fds[0]);
    shared_ptr<LXM::NsManager> ns_manager = std::make_shared<LXM::NsManager>();
    ns_manager->init();
    ns_manager->mount();

    // wait for cgroup apply
    ns_manager->exec();
    return 0;
}
int main (int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    int ret = pipe(fds);
    if (ret < 0) {
        return -1;
    }
    char * stack = (char *) malloc(STACK_SIZE);
    printf("----------cur %d\n", getpid());
    int pid = clone(main_process, stack + STACK_SIZE,
        CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD | CLONE_NEWNET | CLONE_NEWUSER, NULL );
    LXM::CGroupManager cm;
    cm.request("cpu", FLAGS_cpu);
    cm.request("mem", FLAGS_mem);
    cm.apply(pid);
    set_uid_and_gid(pid);
    printf("notify close\n");
    notify_close(fds[1]);
    int status;
    wait(&status);
    return 0;
}