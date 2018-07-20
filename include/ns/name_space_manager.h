#ifndef LXM_NS_NAME_SPACE_MANAGER_H
#define LXM_NS_NAME_SPACE_MANAGER_H
#include <string>
using std::string;
namespace LXM {
class NsManager {
public:
    NsManager();
    void init();
    void mount();
    void exec();
private:
    void mount_root();
    void mount_proc();
private:
    string image_path;
    string root_path;

};
}
#endif