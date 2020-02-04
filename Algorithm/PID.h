#ifndef PID_H
#define PID_H

#include "mbed.h"

class PID{ //Exponential Moving Average Filter
    public:
        PID(float kp, float ki, float kd);
        float getPID(float error); 
    private:
        float kp;
        float ki;
        float kd;
        float last_err;
        float err_sum;
};

#endif