#include "ns/namespace_manager.h"
#include <unistd.h>
#include <sys/mount.h>
#include "flags.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXBUFSIZE 1024
namespace LXM {

int set_map(char *path) {
    FILE * f = fopen(path, "w");
    if (f == NULL) {
        perror("fopen");
        return -1;
    }
    if (fprintf(f, "%d %d %d", 0, 0, 65534) < 0) {
        perror("fprintf");
        return -1;
    }
    if (fclose(f) < 0) {
        perror("fclose");
        return -1;
    }
    return 0;
}

int set_uid_and_gid(pid_t pid) {
    char path[256];
    sprintf(path, "/proc/%d/uid_map", pid);
    set_map(path);
    sprintf(path, "/proc/%d/gid_map", pid);
    set_map(path);
    sprintf(path, "cat /proc/%d/uid_map", pid);
    system(path);
    printf("--------------------------------------%d %s", pid, path);
    return 0;
}

NsManager::NsManager() {
    image_path = FLAGS_image_name;
    root_path = "/home/ly/rootfs";
    cmd = FLAGS_cmd;
}

int NsManager::init() {
    // set_uid_and_gid(getpid());
    if (sethostname("HP", 2) < 0) {
        perror("init failed");
        return -1;
    }
    return 0;
}

int NsManager::mount() {
    if (mount_root() < 0) {
        perror("mount_root");
        return -1;
    }

    if (mount_proc() < 0) {
        perror("mount_proc");
        return -1;
    }
    return 0;
}

int NsManager::exec() {
    char  * const  argv[] = {(char*)"bash", NULL};
    if (execv(cmd.c_str(), argv) < 0) {
        perror((string("exec failed ") + cmd).c_str());
        return -1;
    }
    return 0;
}

int NsManager::mount_root() {
    if (chdir(root_path.c_str()) != 0 || chroot(root_path.c_str()) != 0) {
        perror("mount_root");
        return -1;
    }
    return 0;
}

int NsManager::mount_proc() {
    return ::mount("proc", "/proc", "proc", 0 ,NULL);
}
}