#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tipsyEdit.h"


/*=============================================================================
 Creates an initial condition for a Kelvin-Helmholtz
=============================================================================*/

int main(){
    int i;
    float buffx, buffy, khlambda=128.0;

    // Read in the input glass
    char filename[100] = "glass.std";
    printf("Reading: %s\n", filename);
    tipsy* tipsyIn = readTipsyStd(filename);
    // Set attributes not set by readTipsy
    tipsyIn->attr->xmin = -0.5; tipsyIn->attr->xmax = 0.5;
    tipsyIn->attr->ymin = -0.5; tipsyIn->attr->ymax = 0.5;
    tipsyIn->attr->zmin = -0.5; tipsyIn->attr->zmax = 0.5;
    printf("Input ");
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);
    printf("=================================================\n");

    for(i=0; i<tipsyIn->head->nsph; i++){
        tipsyIn->gas[i].mass *= 2.048e-4;
        tipsyIn->gas[i].rho *= 2.048e-4;
    }

    // Create 32x16x8 unompressed glass
    printf("\nCreating 32x16x8 uncompressed glass:\n");
    tipsy* lowdens = tipsyClone(tipsyIn);
    tipsyScaleExpand(lowdens, 32, 16, 8);
    tipsyTesselate(lowdens, 8, 8, 1);
    tipsyCenter(lowdens);
    for(i=0; i<lowdens->head->nsph; i++){
        lowdens->gas[i].temp = 400000.0;
        lowdens->gas[i].vel[AXIS_X] = 60.0;
    }
    printHeader(lowdens->head);
    printAttr(lowdens->attr);
    printf("=================================================\n");

    // Create 16x16x8 uncompressed glass
    printf("\nCreating 16x16x8 uncompressed glass:\n");
    tipsy* highdens = tipsyClone(tipsyIn);
    tipsyScaleExpand(highdens, 16, 16, 8);
    tipsyTesselate(highdens, 16, 8, 1);
    tipsyCenter(highdens);
    for(i=0; i<highdens->head->nsph; i++){
        highdens->gas[i].temp = 200000.0;
        highdens->gas[i].vel[AXIS_X] = -60.0;
    }
    printHeader(highdens->head);
    printAttr(highdens->attr);
    printf("=================================================\n");

    printf("\nCreating cropped upper and lower lowdensity regions:\n");
    tipsy* lowdenstop = tipsyClone(lowdens);
    tipsyCrop(lowdenstop, cropbot);
    tipsyTranslate(lowdenstop, 0.0, 128.0, 0.0);
    tipsy* lowdensbot = tipsyClone(lowdens);
    tipsyCrop(lowdensbot, croptop);
    tipsyTranslate(lowdensbot, 0.0, -128.0, 0.0);
    printHeader(lowdenstop->head);
    printAttr(lowdenstop->attr);
    printf("\n");
    printHeader(lowdensbot->head);
    printAttr(lowdensbot->attr);
    printf("=================================================\n");

    printf("\nCombining pieces:\n");
    tipsy* lowdenscomb = tipsyJoin(lowdenstop, lowdensbot);
    tipsy* kh = tipsyJoin(highdens, lowdenscomb);
    for(i=0; i<kh->head->nsph; i++){
        buffx = kh->gas[i].pos[AXIS_X];
        buffy = kh->gas[i].pos[AXIS_Y];
        kh->gas[i].vel[AXIS_Y] = 40.0*((sin(2.0*M_PI*buffx/khlambda)*exp(-1.0*pow((buffy-64.0)/26.0, 2.0))) - (sin(2.0*M_PI*buffx/khlambda)*exp(-1.0*pow((buffy+64.0)/26.0, 2.0))));
    }
    printHeader(kh->head);
    printAttr(kh->attr);
    printf("=================================================\n");

    writeTipsyStd("kh.glass.std", kh);

    // Cleanup
    tipsyDestroy(tipsyIn); tipsyDestroy(highdens);
    tipsyDestroy(lowdens);
    tipsyDestroy(lowdenstop); tipsyDestroy(lowdensbot); tipsyDestroy(lowdenscomb);
}

// slice crops
int croptop(void* particle, int type){
    if (type == TYPE_GAS){
        if (((gas_particle*)particle)->pos[AXIS_Y] > 0.0)
            return 1;
        else
            return 0;
    }
    else {
        return 1;
    }
}
int cropbot(void* particle, int type){
    if (type == TYPE_GAS){
        if (((gas_particle*)particle)->pos[AXIS_Y] < 0.0)
            return 1;
        else
            return 0;
    }
    else {
        return 1;
    }
}
