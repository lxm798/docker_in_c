#ifndef LXM_RES_HANDLER_H
#define LXM_RES_HANDLER_H
#include <string>
#include <fstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::ios;
using std::endl;
using std::cout;
using std::string;
namespace LXM {
class ResHandler {
public:
    virtual int init(const string &name) = 0;
    virtual int apply(int pid, float v) = 0;
    virtual ~ResHandler() {};
protected:
    bool is_dir_exist(const string &dir_path);
    int create_dir_if_not_exist(const string & dir_path);
    template<typename T>
    int append_to_file(const string & path, T t);
    template<typename T>
    int write_to_file(const string &path, T t); 
};

template<typename T>
int ResHandler::append_to_file(const string & path, T t) {
    ofstream ofs(path.c_str(), ios::out | ios::app);
    if (!ofs.good()) {
        ofs.close();
        return -1;
    }
    ofs << t << endl;
    ofs.close();
    return 0;
}
template<typename T>
int ResHandler::write_to_file(const string &path, T t) {
    std::cout << path << ":" << t << std::endl;
    ofstream ofs(path.c_str(), ios::out | ios::trunc);
    if (!ofs.good()) {
            std::cout << path << "openfailed" << std::endl;
        ofs.close();
        return -1;
    }
    ofs << t << endl;
    ofs.close();
    return 0;
}
}
#endif