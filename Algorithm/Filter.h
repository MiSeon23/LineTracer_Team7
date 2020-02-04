#ifndef FILTER_H
#define FILTER_H

#include "mbed.h"

class EMAF{ //Exponential Moving Average Filter
    public:
        EMAF(float weight);
        float getEMAF(int val); 
    private:
        float filtered_val;
        float alpha;
        float pre_val;
        int LData[100];
};

#endif