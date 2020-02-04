#include "LineDetect.h"

#define LLL 0
#define LL  1
#define L   2
#define S   3
#define R   4
#define RR  5
#define RRR 6

//max : 36 , -32

Servo servo (p10);
LaneSensor laneSensor(p11,p12,p13,p14,p15,p16,p17);
PID pid(0.862, 0.0, 0.0); //0.86//0.44//0.455
EMAF emaf(0.18);//0.18//0.2

char linestate, beforestate;
int laneData;
float degree, err, controlled_degree;

void LineDetect::Lineinit(){
    servo.update(0.0);
}

int LineDetect::LineDetect_run(){
    laneData = laneSensor.getData();
        
    if( laneData == 0x7e )      linestate = LLL;
    else if( laneData == 0x7d ) linestate = LL;
    else if( laneData == 0x7b ) linestate = L;
    else if( laneData == 0x77 ) linestate = S;
    else if( laneData == 0x6f ) linestate = R;    
    else if( laneData == 0x5f ) linestate = RR;
    else if( laneData == 0x3f ) linestate = RRR;
    else linestate = beforestate;
    return linestate;
}

void LineDetect::LineTrace_run(){
    err = laneSensor.getError();
    degree = emaf.getEMAF(err/2.);
    
//    degree = -err/2.;
}

void LineDetect::Line_update(){
    controlled_degree = degree + pid.getPID(degree - servo.getDegree());
    servo.update(controlled_degree);
//    servo.update(degree);
}

