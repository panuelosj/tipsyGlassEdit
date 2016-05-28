#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

//=============================================================================
//-------------------------ENDIAN-SWAPS----------------------------------------
//=============================================================================
float swapEndianFloat(const float valIn){
    float valOut;
    char *swapIn = (char*)&valIn;
    char *swapOut = (char*)&valOut;

    swapOut[0] = swapIn[3];
    swapOut[1] = swapIn[2];
    swapOut[2] = swapIn[1];
    swapOut[3] = swapIn[0];

    return valOut;
}
int swapEndianInt(const int valIn){
    int valOut;
    char *swapIn = (char*)&valIn;
    char *swapOut = (char*)&valOut;

    swapOut[0] = swapIn[3];
    swapOut[1] = swapIn[2];
    swapOut[2] = swapIn[1];
    swapOut[3] = swapIn[0];

    return valOut;
}
double swapEndianDouble(const double valIn){
    double valOut;
    char *swapIn = (char*)&valIn;
    char *swapOut = (char*)&valOut;

    swapOut[0] = swapIn[7];
    swapOut[1] = swapIn[6];
    swapOut[2] = swapIn[5];
    swapOut[3] = swapIn[4];
    swapOut[4] = swapIn[3];
    swapOut[5] = swapIn[2];
    swapOut[6] = swapIn[1];
    swapOut[7] = swapIn[0];

    return valOut;
}
