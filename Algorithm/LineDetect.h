#ifndef LINEDETECT_H
#define LINEDETECT_H

#include "mbed.h"
#include "Servo.h"
#include "LaneSensor.h"
#include "PID.h"

class LineDetect{
    public:
        void Lineinit();
        int LineDetect_run();
        void LineTrace_run();
        void Line_update();
    protected:
        int laneData;
        float degree;
        char linestate, beforestate;
};

#endif