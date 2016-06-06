#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../tipsyEdit.h"

int main(int argc, char *argv[]){
    if (argc != 12) {
        system("cat nagato");
        printf("Error: not enough arguments\n");
        printf("Usage:\n\t %s [fileIn] [fileOut] [xTesselate] [yTesselate] [zTesselate] [xMin] [xMax] [yMin] [yMax] [zMin] [zMax]\n", argv[0]);
        exit(-1);
        //errorCase(ERR_MISSING_ARGS);                                            //errorCase() automatically exits the program
    }
    // Read in the input glass, filename as given in main's argument
    printf("Reading: %s\n", argv[1]);
    tipsy* tipsyIn = readTipsyStd(argv[1]);
    printHeader(tipsyIn->head);

    // Fix attributes first - necessary for tiling properly since the default
        // attributes are just the max min particles; not doing this will tile
        // the simulation box with the extrema at the very edge of the box
    tipsyIn->attr->xmin = strtof(argv[6], NULL);
    tipsyIn->attr->xmax = strtof(argv[7], NULL);
    tipsyIn->attr->ymin = strtof(argv[8], NULL);
    tipsyIn->attr->ymax = strtof(argv[9], NULL);
    tipsyIn->attr->zmin = strtof(argv[10], NULL);
    tipsyIn->attr->zmax = strtof(argv[11], NULL);
    printAttr(tipsyIn->attr);
    printf("=================================================\n");

    tipsyTesselate(tipsyIn,
                    (int)strtol(argv[3], NULL, 10),
                    (int)strtol(argv[4], NULL, 10),
                    (int)strtol(argv[5], NULL, 10));
    printf("Writing to: %s\n", argv[2]);
    writeTipsyStd(argv[2], tipsyIn);
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);

    // Cleanup
    tipsyDestroy(tipsyIn);
}
