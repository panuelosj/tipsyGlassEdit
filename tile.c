#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"


//=============================================================================
//-------------------------ACTUAL-CODE-----------------------------------------
//=============================================================================

int main(){
    // Indexing Variables
    int i,j,k;
    // Read in the input glass
    char filename[100] = "glass.std";
    printf("Reading: %s\n", filename);
    tipsy* glassIn = readTipsyStd(filename);
    // Set attributes not set by readTipsy
    glassIn->attr->xmin = -0.5; glassIn->attr->xmax = 0.5;
    glassIn->attr->ymin = -0.5; glassIn->attr->ymax = 0.5;
    glassIn->attr->zmin = -0.5; glassIn->attr->zmax = 0.5;
    printf("Input ");
    printHeader(glassIn->header);
    printAttr(glassIn->attr);
    printf("=================================================\n");

    // Create 8x compressed glass
    printf("\nCreating 8x compressed glass:\n");
    tipsy* glass8x = tipsyClone(glassIn);
    tipsyScaleShrink(glass8x, 2, 2, 2);
    tipsyTesselate(glass8x, 2, 2, 2);
    tipsyCenter(glass8x);
    printHeader(glass8x->header);
    printAttr(glass8x->attr);
    printf("=================================================\n");
    writeTipsyStd("glass8x.std", glass8x);

    // Create 1/8x compressed glass
    printf("\nCreating 1/8x compressed glass:\n");
    tipsy* glass8f = tipsyClone(glassIn);
    tipsyScaleExpand(glass8f, 2, 2, 2);
    tipsyCenter(glass8f);
    printHeader(glass8f->header);
    printAttr(glass8f->attr);
    printf("=================================================\n");
    writeTipsyStd("glass8f.std", glass8f);

    // Tile the two base units
    printf("\nCreating Sod Shocktube:\n");
    tipsyTesselate(glass8f, 7, 1, 1);           // creates 14x2x2
    tipsyTranslate(glass8f, 1, 0, 0);           // pushes the lower density to only the positive x axis
    tipsyTesselate(glassIn, 14, 2, 2);          // creates 14x2x2
    tipsyTranslate(glassIn, -13.5, -0.5, -0.5); // pushes the high density to the negative x axis
    tipsy* sodShocktube = tipsyJoin(glassIn, glass8f);
    printHeader(sodShocktube->header);
    printAttr(sodShocktube->attr);
    printf("=================================================\n");
    writeTipsyStd("sodShocktube.std", sodShocktube);

}
