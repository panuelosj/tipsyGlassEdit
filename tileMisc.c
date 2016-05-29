#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

//=============================================================================
//-------------------------STRUCT ALLOCATION-----------------------------------
//=============================================================================
tipsy* createTipsy(const double simtime, const int nsph, const int ndark, const int nstar){
    int i;
    // Create object (pointer to a struct of pointers to memory)
    tipsy* newTipsy = malloc(sizeof(tipsy));
    // Allocate and create header
    newTipsy->header = malloc(sizeof(header));
    newTipsy->header->simtime = simtime;
    newTipsy->header->nbodies = nsph + ndark + nstar;
    newTipsy->header->ndim = 3;
    newTipsy->header->nsph = nsph;
    newTipsy->header->ndark = ndark;
    newTipsy->header->nstar = nstar;
    newTipsy->header->pad = 0;
    // Allocate space for gas particles and set default values
    if (newTipsy->header->nsph != 0){
        newTipsy->gas = malloc(newTipsy->header->nsph*sizeof(gas_particle));
        for (i=0; i < newTipsy->header->nsph; i++){
            newTipsy->gas[i].mass = 1.0;
            newTipsy->gas[i].pos[0] = VAL_NaN;
            newTipsy->gas[i].pos[1] = VAL_NaN;
            newTipsy->gas[i].pos[2] = VAL_NaN;
            newTipsy->gas[i].vel[0] = 0.0;
            newTipsy->gas[i].vel[1] = 0.0;
            newTipsy->gas[i].vel[2] = 0.0;
            newTipsy->gas[i].rho = 1.0;
            newTipsy->gas[i].temp = 1.0;
            newTipsy->gas[i].eps = 1.0;
            newTipsy->gas[i].metals = 0.0;
            newTipsy->gas[i].phi = 1.0;
        }
    } else newTipsy->gas = NULL;
    // Allocate space for dark particles and set default values
    if (newTipsy->header->ndark != 0){
        newTipsy->dark = malloc(newTipsy->header->ndark*sizeof(dark_particle));
        for (i=0; i < newTipsy->header->ndark; i++){
            newTipsy->dark[i].mass = 1.0;
            newTipsy->dark[i].pos[0] = VAL_NaN;
            newTipsy->dark[i].pos[1] = VAL_NaN;
            newTipsy->dark[i].pos[2] = VAL_NaN;
            newTipsy->dark[i].vel[0] = 0.0;
            newTipsy->dark[i].vel[1] = 0.0;
            newTipsy->dark[i].vel[2] = 0.0;
            newTipsy->dark[i].eps = 1.0;
            newTipsy->dark[i].phi = 1.0;
        }
    } else newTipsy->dark = NULL;
    // Allocate space for star particles and set default values
    if (newTipsy->header->nstar != 0){
        newTipsy->star = malloc(newTipsy->header->nstar*sizeof(star_particle));
        for (i=0; i < newTipsy->header->nstar; i++){
            newTipsy->star[i].mass = 1.0;
            newTipsy->star[i].pos[0] = VAL_NaN;
            newTipsy->star[i].pos[1] = VAL_NaN;
            newTipsy->star[i].pos[2] = VAL_NaN;
            newTipsy->star[i].vel[0] = 0.0;
            newTipsy->star[i].vel[1] = 0.0;
            newTipsy->star[i].vel[2] = 0.0;
            newTipsy->star[i].metals = 0.0;
            newTipsy->star[i].tform = 0.0;
            newTipsy->star[i].eps = 1.0;
            newTipsy->star[i].phi = 1.0;
        }
    } else newTipsy->star = NULL;

    return newTipsy;
}


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
void swapEndianBatch(const tipsy* tipsyIn, const int type, const int i){
    if (type == TYPE_HEADER) {
        tipsyIn->header->simtime = swapEndianDouble(tipsyIn->header->simtime);
        tipsyIn->header->nbodies = swapEndianInt(tipsyIn->header->nbodies);
        tipsyIn->header->ndim = swapEndianInt(tipsyIn->header->ndim);
        tipsyIn->header->nsph = swapEndianInt(tipsyIn->header->nsph);
        tipsyIn->header->ndark = swapEndianInt(tipsyIn->header->ndark);
        tipsyIn->header->nstar = swapEndianInt(tipsyIn->header->nstar);
    } else if (type == TYPE_GAS) {
        tipsyIn->gas[i].mass = swapEndianFloat(tipsyIn->gas[i].mass);
        tipsyIn->gas[i].pos[0] = swapEndianFloat(tipsyIn->gas[i].pos[0]);
        tipsyIn->gas[i].pos[1] = swapEndianFloat(tipsyIn->gas[i].pos[1]);
        tipsyIn->gas[i].pos[2] = swapEndianFloat(tipsyIn->gas[i].pos[2]);
        tipsyIn->gas[i].vel[0] = swapEndianFloat(tipsyIn->gas[i].vel[0]);
        tipsyIn->gas[i].vel[1] = swapEndianFloat(tipsyIn->gas[i].vel[1]);
        tipsyIn->gas[i].vel[2] = swapEndianFloat(tipsyIn->gas[i].vel[2]);
        tipsyIn->gas[i].rho = swapEndianFloat(tipsyIn->gas[i].rho);
        tipsyIn->gas[i].temp = swapEndianFloat(tipsyIn->gas[i].temp);
        tipsyIn->gas[i].eps = swapEndianFloat(tipsyIn->gas[i].eps);
        tipsyIn->gas[i].metals = swapEndianFloat(tipsyIn->gas[i].metals);
        tipsyIn->gas[i].phi = swapEndianFloat(tipsyIn->gas[i].phi);
    } else if (type == TYPE_DARK) {
        tipsyIn->dark[i].mass = swapEndianFloat(tipsyIn->dark[i].mass);
        tipsyIn->dark[i].pos[0] = swapEndianFloat(tipsyIn->dark[i].pos[0]);
        tipsyIn->dark[i].pos[1] = swapEndianFloat(tipsyIn->dark[i].pos[1]);
        tipsyIn->dark[i].pos[2] = swapEndianFloat(tipsyIn->dark[i].pos[2]);
        tipsyIn->dark[i].vel[0] = swapEndianFloat(tipsyIn->dark[i].vel[0]);
        tipsyIn->dark[i].vel[1] = swapEndianFloat(tipsyIn->dark[i].vel[1]);
        tipsyIn->dark[i].vel[2] = swapEndianFloat(tipsyIn->dark[i].vel[2]);
        tipsyIn->dark[i].eps = swapEndianFloat(tipsyIn->dark[i].eps);
        tipsyIn->dark[i].phi = swapEndianFloat(tipsyIn->dark[i].phi);
    } else if (type == TYPE_STAR) {
        tipsyIn->star[i].mass = swapEndianFloat(tipsyIn->star[i].mass);
        tipsyIn->star[i].pos[0] = swapEndianFloat(tipsyIn->star[i].pos[0]);
        tipsyIn->star[i].pos[1] = swapEndianFloat(tipsyIn->star[i].pos[1]);
        tipsyIn->star[i].pos[2] = swapEndianFloat(tipsyIn->star[i].pos[2]);
        tipsyIn->star[i].vel[0] = swapEndianFloat(tipsyIn->star[i].vel[0]);
        tipsyIn->star[i].vel[1] = swapEndianFloat(tipsyIn->star[i].vel[1]);
        tipsyIn->star[i].vel[2] = swapEndianFloat(tipsyIn->star[i].vel[2]);
        tipsyIn->star[i].metals = swapEndianFloat(tipsyIn->star[i].metals);
        tipsyIn->star[i].tform = swapEndianFloat(tipsyIn->star[i].tform);
        tipsyIn->star[i].eps = swapEndianFloat(tipsyIn->star[i].eps);
        tipsyIn->star[i].phi = swapEndianFloat(tipsyIn->star[i].phi);
    }
}
