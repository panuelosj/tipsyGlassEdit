#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tipsyEdit.h"


/*=============================================================================
 Creates an initial condition for a shocktube
=============================================================================*/

int main(){
    int i;

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

    // Create 1/8x compressed glass
    printf("\nCreating 1/8x compressed glass:\n");
    tipsy* glass8f = tipsyClone(tipsyIn);
    tipsyScaleExpand(glass8f, 2, 2, 2);
    tipsyCenter(glass8f);
    printHeader(glass8f->head);
    printAttr(glass8f->attr);
    printf("=================================================\n");
    writeTipsyStd("glass8f.std", glass8f);

    // Tile the 1/8x compressed glass to 28x2x2
    printf("\nTiling Shocktube:\n");
    tipsy* rcrShock = tipsyClone(glass8f);
    tipsyTesselate(rcrShock, 14, 1, 1);           // creates 28x2x2
    printf("\nCentering:\n");
    tipsyCenter(rcrShock);
    printf("\nEditing Velocities:\n");
    for (i=0; i<rcrShock->head->nsph; i++){
        rcrShock->gas[i].vel[AXIS_X] = (2.0/(1.0+exp(10.0*rcrShock->gas[i].pos[AXIS_X])))-1.0;
    }
    printHeader(rcrShock->head);
    printAttr(rcrShock->attr);

    writeTipsyStd("SCSSmooth.std", rcrShock);

    // Cleanup
    tipsyDestroy(tipsyIn); tipsyDestroy(glass8f); tipsyDestroy(rcrShock);
}
