#ifndef LXM_NS_NAME_SPACE_MANAGER_H
#define LXM_NS_NAME_SPACE_MANAGER_H
#include <string>
using std::string;
namespace LXM {
class NsManager {
public:
    NsManager();
    int init();
    int mount();
    int exec();
private:
    int mount_root();
    int mount_proc();
private:
    string image_path;
    string root_path;
    string cmd;
    char ** argv;
};
}
#endif