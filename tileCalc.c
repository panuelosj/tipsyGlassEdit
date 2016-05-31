#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"


tipsy* tipsyCompress(tipsy* tipsyIn, const float xCompress, const float yCompress, const float zCompress){
    // Indexing Variables
    int i;

    int totalCompress = xCompress*yCompress*zCompress;
    tipsy* tipsyTileCompressed = createTipsy(0,
        tipsyIn->header->nsph,
        tipsyIn->header->ndark,
        tipsyIn->header->nstar);
    tipsy* tipsyOut = createTipsy(0,
        tipsyIn->header->nsph * totalCompress,
        tipsyIn->header->ndark * totalCompress,
        tipsyIn->header->nstar * totalCompress);
    tipsyTileCompressed->attr->xmin = tipsyIn->attr->xmin;
    tipsyTileCompressed->attr->xmax = tipsyIn->attr->xmax;
    tipsyTileCompressed->attr->ymin = tipsyIn->attr->ymin;
    tipsyTileCompressed->attr->ymax = tipsyIn->attr->ymax;
    tipsyTileCompressed->attr->zmin = tipsyIn->attr->zmin;
    tipsyTileCompressed->attr->zmax = tipsyIn->attr->zmax;
    // Copy all gas particles
    memcpy(tipsyTileCompressed->gas, tipsyIn->gas, tipsyIn->header->nsph*sizeof(gas_particle));
    // Copy all dark particles
    memcpy(tipsyTileCompressed->dark, tipsyIn->dark, tipsyIn->header->ndark*sizeof(dark_particle));
    // Copy all star particles
    memcpy(tipsyTileCompressed->star, tipsyIn->star, tipsyIn->header->nstar*sizeof(star_particle));
    tipsyScaleShrink(tipsyTileCompressed, 2, 3, 1);
    return tipsyTileCompressed;
}

void tipsyTesselate(tipsy* tipsyIn, const int xTile, const int yTile, const int ztile){

}

void tipsyScaleShrink(tipsy* tipsyIn, const int xShrink, const int yShrink, const int zShrink){
    /* Shrinks the tipsy object in each dimension by the given scaling factors
        by dividing by that value. For consistency with other functions, only
        integer values should be given for the shrinking factors, but are
        casted to floats to give a float result when dividing.

        Parameters:
            tipsy* tipsyIn      - pointer to the tipsy struct to be shrunk
            const int xShrink   - x dimension compression factor
            const int yShrink   - y dimension compression factor
            const int zShrink   - z dimension compression factor
        Return:
            void
    */

    // Indexing Variables
    int i;
    // Float casts
    const float xShrinkF = (float) xShrink;
    const float yShrinkF = (float) yShrink;
    const float zShrinkF = (float) zShrink;

    // Shrink each element's coordinates by the scaling factor given
    for (i=0; i < tipsyIn->header->nsph; i++){
        tipsyIn->gas[i].pos[AXIS_X] /= xShrinkF;
        tipsyIn->gas[i].pos[AXIS_Y] /= yShrinkF;
        tipsyIn->gas[i].pos[AXIS_Z] /= zShrinkF;
    }
    for (i=0; i < tipsyIn->header->ndark; i++){
        tipsyIn->dark[i].pos[AXIS_X] /= xShrinkF;
        tipsyIn->dark[i].pos[AXIS_Y] /= yShrinkF;
        tipsyIn->dark[i].pos[AXIS_Z] /= zShrinkF;
    }
    for (i=0; i < tipsyIn->header->nstar; i++){
        tipsyIn->star[i].pos[AXIS_X] /= xShrinkF;
        tipsyIn->star[i].pos[AXIS_Y] /= yShrinkF;
        tipsyIn->star[i].pos[AXIS_Z] /= zShrinkF;
    }

    // Shrink each boundary by the scaling factor given
    tipsyIn->attr->xmin /= xShrinkF; tipsyIn->attr->xmax /= xShrinkF;
    tipsyIn->attr->ymin /= yShrinkF; tipsyIn->attr->ymax /= yShrinkF;
    tipsyIn->attr->zmin /= zShrinkF; tipsyIn->attr->zmax /= zShrinkF;
}

//=============================================================================
//-------------------------COMPARISONS-----------------------------------------
//=============================================================================

void autoFindBounds(tipsy* tipsyIn){
    // Indexing variables
    int i=0;
    // Set initial max and min based on the first particle
    if (tipsyIn->header->nsph != 0) {
        tipsyIn->attr->xmin = tipsyIn->gas[i].pos[AXIS_X];
        tipsyIn->attr->xmax = tipsyIn->gas[i].pos[AXIS_X];
        tipsyIn->attr->ymin = tipsyIn->gas[i].pos[AXIS_Y];
        tipsyIn->attr->ymax = tipsyIn->gas[i].pos[AXIS_Y];
        tipsyIn->attr->zmin = tipsyIn->gas[i].pos[AXIS_Z];
        tipsyIn->attr->zmax = tipsyIn->gas[i].pos[AXIS_Z];
    } else if (tipsyIn->header->ndark != 0) {
        tipsyIn->attr->xmin = tipsyIn->gas[i].pos[AXIS_X];
        tipsyIn->attr->xmax = tipsyIn->gas[i].pos[AXIS_X];
        tipsyIn->attr->ymin = tipsyIn->gas[i].pos[AXIS_Y];
        tipsyIn->attr->ymax = tipsyIn->gas[i].pos[AXIS_Y];
        tipsyIn->attr->zmin = tipsyIn->gas[i].pos[AXIS_Z];
        tipsyIn->attr->zmax = tipsyIn->gas[i].pos[AXIS_Z];
    } else if (tipsyIn->header->nstar != 0) {
        tipsyIn->attr->xmin = tipsyIn->star[i].pos[AXIS_X];
        tipsyIn->attr->xmax = tipsyIn->star[i].pos[AXIS_X];
        tipsyIn->attr->ymin = tipsyIn->star[i].pos[AXIS_Y];
        tipsyIn->attr->ymax = tipsyIn->star[i].pos[AXIS_Y];
        tipsyIn->attr->zmin = tipsyIn->star[i].pos[AXIS_Z];
        tipsyIn->attr->zmax = tipsyIn->star[i].pos[AXIS_Z];
    } else errorCase(ERR_NO_PARTICLES);
    // Find max min that changes
    for (i=1; i<tipsyIn->header->nsph; i++){
        if (tipsyIn->gas[i].pos[AXIS_X] < tipsyIn->attr->xmin)
            tipsyIn->attr->xmin = tipsyIn->gas[i].pos[AXIS_X];
        else if (tipsyIn->gas[i].pos[AXIS_X] > tipsyIn->attr->xmax)
            tipsyIn->attr->xmax = tipsyIn->gas[i].pos[AXIS_X];
        if (tipsyIn->gas[i].pos[AXIS_Y] < tipsyIn->attr->ymin)
            tipsyIn->attr->ymin = tipsyIn->gas[i].pos[AXIS_Y];
        else if (tipsyIn->gas[i].pos[AXIS_Y] > tipsyIn->attr->ymax)
            tipsyIn->attr->ymax = tipsyIn->gas[i].pos[AXIS_Y];
        if (tipsyIn->gas[i].pos[AXIS_Z] < tipsyIn->attr->zmin)
            tipsyIn->attr->zmin = tipsyIn->gas[i].pos[AXIS_Z];
        else if (tipsyIn->gas[i].pos[AXIS_Z] > tipsyIn->attr->zmax)
            tipsyIn->attr->zmax = tipsyIn->gas[i].pos[AXIS_Z];
    }
    for (i=1; i<tipsyIn->header->ndark; i++){
        if (tipsyIn->dark[i].pos[AXIS_X] < tipsyIn->attr->xmin)
            tipsyIn->attr->xmin = tipsyIn->dark[i].pos[AXIS_X];
        else if (tipsyIn->dark[i].pos[AXIS_X] > tipsyIn->attr->xmax)
            tipsyIn->attr->xmax = tipsyIn->dark[i].pos[AXIS_X];
        if (tipsyIn->dark[i].pos[AXIS_Y] < tipsyIn->attr->ymin)
            tipsyIn->attr->ymin = tipsyIn->dark[i].pos[AXIS_Y];
        else if (tipsyIn->dark[i].pos[AXIS_Y] > tipsyIn->attr->ymax)
            tipsyIn->attr->ymax = tipsyIn->dark[i].pos[AXIS_Y];
        if (tipsyIn->dark[i].pos[AXIS_Z] < tipsyIn->attr->zmin)
            tipsyIn->attr->zmin = tipsyIn->dark[i].pos[AXIS_Z];
        else if (tipsyIn->dark[i].pos[AXIS_Z] > tipsyIn->attr->zmax)
            tipsyIn->attr->zmax = tipsyIn->dark[i].pos[AXIS_Z];
    }
    for (i=1; i<tipsyIn->header->nstar; i++){
        if (tipsyIn->star[i].pos[AXIS_X] < tipsyIn->attr->xmin)
            tipsyIn->attr->xmin = tipsyIn->star[i].pos[AXIS_X];
        else if (tipsyIn->star[i].pos[AXIS_X] > tipsyIn->attr->xmax)
            tipsyIn->attr->xmax = tipsyIn->star[i].pos[AXIS_X];
        if (tipsyIn->star[i].pos[AXIS_Y] < tipsyIn->attr->ymin)
            tipsyIn->attr->ymin = tipsyIn->star[i].pos[AXIS_Y];
        else if (tipsyIn->star[i].pos[AXIS_Y] > tipsyIn->attr->ymax)
            tipsyIn->attr->ymax = tipsyIn->star[i].pos[AXIS_Y];
        if (tipsyIn->star[i].pos[AXIS_Z] < tipsyIn->attr->zmin)
            tipsyIn->attr->zmin = tipsyIn->star[i].pos[AXIS_Z];
        else if (tipsyIn->star[i].pos[AXIS_Z] > tipsyIn->attr->zmax)
            tipsyIn->attr->zmax = tipsyIn->star[i].pos[AXIS_Z];
    }
}
