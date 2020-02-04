#include "Filter.h"

EMAF::EMAF(float weight)
{ 
    alpha=weight;
    pre_val = 0.0;
    filtered_val = 0.0;
}

int i = 0;
char flag = 0;

float EMAF::getEMAF(int val){
    if( i < 100 ) {//
        LData[i] = val;
        i++;
    }
    else{
        if(flag == 0){
            for(int j = 0; j<100; j++){
                filtered_val = alpha * pre_val + (1-alpha)*LData[i];
                pre_val = filtered_val;
            }
            flag = 1;
        }
        else if(flag){
            filtered_val = alpha * pre_val + (1-alpha)*val;
            pre_val = filtered_val;
        }
    }
    if( i < 100 ) return (float)val;
    else return filtered_val;
}