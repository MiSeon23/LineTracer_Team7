#include "mbed.h"
#include "DistanceSensor.h"
#include "Motor.h"
#include "Servo.h"
#include "LineDetect.h"

LineDetect linedetect;
DistanceSensor pir(p20);
Motor motor (p23, p24, p25, p26);

unsigned int uiFlag_1ms = 0;
unsigned int uiFlag_10ms = 0;
unsigned int uiFlag_20ms = 0;
    
void counter_1ms ()
{
    uiFlag_1ms++;
    uiFlag_10ms++;
    uiFlag_20ms++;
}


// Plot distance sensor
int main()
{
    wait(1);

    linedetect.Lineinit();
    
    float dis = 0.0;
    float goal_speed = 0.0;
    int linestate;
    
    while(1){        
        motor.setSpeed_percent(goal_speed, BACKWARD);

        linestate = linedetect.LineDetect_run();
        dis = pir.getDistance_cm();
        linedetect.LineTrace_run();
        linedetect.Line_update();
            
        if(dis>6 && dis<80){ //80
            goal_speed = 0.0;
            motor.setSpeed_percent(goal_speed, BREAK);
        }
        else if( dis>=80 ){
            if((linestate == 0) || (linestate == 6) ) goal_speed = 16.0;
            else if((linestate == 1) || (linestate == 5) ) goal_speed = 17.0;
            else if((linestate == 2) || (linestate == 4) ) goal_speed = 24.5;
            else if( linestate == 3 ) goal_speed = 24.5;        
        }
    }
}
