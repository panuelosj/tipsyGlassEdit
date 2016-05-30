#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

tipsy* tileCompress(tipsy* tipsyIn, const float xCompress, const float yCompress, const float zCompress){
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
    // Copy all gas particles
    memcpy(tipsyTileCompressed->gas, tipsyIn->gas, tipsyIn->header->nsph*sizeof(gas_particle));
    for (i=0; i < tipsyTileCompressed->header->nsph; i++){
        tipsyTileCompressed->gas[i].pos[0] /= xCompress;
        tipsyTileCompressed->gas[i].pos[1] /= yCompress;
        tipsyTileCompressed->gas[i].pos[2] /= zCompress;
    }
    // Copy all dark particles
    memcpy(tipsyTileCompressed->dark, tipsyIn->dark, tipsyIn->header->ndark*sizeof(dark_particle));
    for (i=0; i < tipsyTileCompressed->header->ndark; i++){
        tipsyTileCompressed->dark[i].pos[0] /= xCompress;
        tipsyTileCompressed->dark[i].pos[1] /= yCompress;
        tipsyTileCompressed->dark[i].pos[2] /= zCompress;
    }
    // Copy all star particles
    memcpy(tipsyTileCompressed->star, tipsyIn->star, tipsyIn->header->nstar*sizeof(star_particle));
    for (i=0; i < tipsyTileCompressed->header->nstar; i++){
        tipsyTileCompressed->star[i].pos[0] /= xCompress;
        tipsyTileCompressed->star[i].pos[1] /= yCompress;
        tipsyTileCompressed->star[i].pos[2] /= zCompress;
    }
    return tipsyTileCompressed;
}

void tileScaleShrink(tipsy* tipsyIn, const float xShrink, const float yShrink, const float zShrink){
    // Indexing Variables
    int i;
    // Shrink each dimension by the scaling factor given
    for (i=0; i < tipsyIn->header->nsph; i++){
        tipsyIn->gas[i].pos[0] /= xShrink;
        tipsyIn->gas[i].pos[1] /= yShrink;
        tipsyIn->gas[i].pos[2] /= zShrink;
    }
    for (i=0; i < tipsyIn->header->ndark; i++){
        tipsyIn->dark[i].pos[0] /= xShrink;
        tipsyIn->dark[i].pos[1] /= yShrink;
        tipsyIn->dark[i].pos[2] /= zShrink;
    }
    for (i=0; i < tipsyIn->header->nstar; i++){
        tipsyIn->star[i].pos[0] /= xShrink;
        tipsyIn->star[i].pos[1] /= yShrink;
        tipsyIn->star[i].pos[2] /= zShrink;
    }
}
