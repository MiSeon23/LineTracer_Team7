#include "PID.h"

#define DELTA_T 0.05

float err_sum = 0.0;
float delta_err = 0.0;
float last_err = 0.0;

float kp, ki, kd;

//float max_windup = 100.0;
//float umax = 100.0;
//float umin = -100.0;

PID::PID(float kp, float ki, float kd){
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    
    this->err_sum = 0.0;
    this->last_err = 0.0;
}

float PID::getPID(float error){
    float err = error;
    err_sum += err*DELTA_T;
    float delta_err = err - last_err;
    
//    if(delta_err > 10.0){
//        delta_err = 0.0;
//    }
    
    
    last_err = err;
    
//    if(err_sum > max_windup) {
//        err_sum = max_windup;
//    } else if(err_sum < -1.0*max_windup) {
//        err_sum = max_windup*-1.0;
//    }    
    
    
    float p = kp * err;
    float i = ki * err_sum;
    float d = kd * (delta_err/DELTA_T);
    
    float u = p + i + d;

//    if(u > umax) {
//        u = umax;
//    } else if(u < umin) {
//        u = umin;
//    }

    return u;
    
}