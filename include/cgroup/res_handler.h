#ifndef LXM_RES_HANDLER_H
#define LXM_RES_HANDLER_H
class ResHandler {
public:
    virtual void Apply(float v) = 0;
    virtual ~ResHandler() {};
};
#endif