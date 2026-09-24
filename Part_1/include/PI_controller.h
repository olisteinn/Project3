#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

class PI_controller {
    private:
        double parm;
    public:
        PI_controller(double parm_arg);
        double update(double ref, double actual);
};

#endif