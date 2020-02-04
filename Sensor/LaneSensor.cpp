#include "LaneSensor.h"

LaneSensor::LaneSensor(PinName lll,PinName ll,PinName l,PinName m,PinName r,PinName rr,PinName rrr)
    : sensorsIn_(lll,ll,l,m,r,rr,rrr)
{
    error_=0.0;
    prevError_=0.0;
    //sensorsIn_.mode(PullNode);
}
    

float LaneSensor::getError()
{
    bool lll=false;
    bool ll=false;
    bool l=false;
    bool m=false;
    bool r=false;
    bool rr=false;
    bool rrr=false;

    float errorSum=0;
    int errorCount=0;
    float errorConstant =18.5;

//-32 : 36

    int sensorIn=sensorsIn_ & sensorsIn_.mask();
    if( (sensorIn&0x7f)==0x7e  || ((sensorIn&0x7f)==0x7c)) { 
        lll=true;
        errorSum+=errorConstant*-3.3;//-3.45;
        errorCount++;
    }
    if(((sensorIn&0x7f)==0x7d)) {
        ll=true;
        errorSum+=errorConstant*-0.8;//-0.76711;
        errorCount++;
    }
    if(((sensorIn&0x7f)==0x7b) || ((sensorIn&0x7f)==0x7a)) {
        l=true;
        errorSum+=errorConstant*-0.3111;
        errorCount++;
    }
    if(((sensorIn&0x7f)==0x77) || ((sensorIn&0x7f)==0x76)) {
        m=true;
        errorSum+=0.0;
        errorCount++;
    }
    if((sensorIn&0x7f)==0x6f || ((sensorIn&0x7f)==0x6e)) {
        r=true;
        errorSum+=errorConstant*0.35;//-0.325;//-0.3;//-0.4;
        errorCount++;
    }
    if((sensorIn&0x7f)==0x5f || ((sensorIn&0x7f)==0x5e)) {
        rr=true;
        errorSum+=errorConstant*0.863;//-2.8421;//-1.3684;//-1.421;//-1.0526;//-0.916;
        errorCount++;
    }
    if(((sensorIn&0x7f)==0x3f) || ((sensorIn&0x8f)==0x3e)) {
        rrr=true;
        errorSum+=errorConstant*3.7125;//3.88125;
        errorCount++;
    }


    if(errorCount==0) {
        error_=prevError_;
    } else {
        error_=errorSum/((float)errorCount);
    }
    prevError_=error_;

    return error_;
}

int LaneSensor::getData()
{

    return sensorsIn_ & sensorsIn_.mask();;
}