#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

tipsy* readTipsyStd(const char filename[]){
    int i;

    FILE *fp = fopen(filename, "r");
    // Create object
    tipsy* newTipsy = malloc(sizeof(tipsy));

    // Create header
    newTipsy->header = malloc(sizeof(header));                                  // Allocate space
    fread(&newTipsy->header->simtime, sizeof(double), 1, fp);                   // Read in binary
    fread(&newTipsy->header->nbodies, sizeof(int), 6, fp);
    swapEndianBatch(newTipsy, TYPE_HEADER, 0);                                  // Swap endianness
    // Create gas particles
    if (newTipsy->header->nsph != 0){                                           // Check if particles exist
        newTipsy->gas = malloc(newTipsy->header->nsph*sizeof(gas_particle));    // Allocate space
        for (i=0; i < newTipsy->header->nsph; i++){
            fread(&newTipsy->gas[i].mass, sizeof(float), 12, fp);               // Read in binary
            swapEndianBatch(newTipsy, TYPE_GAS, i);                             // Swap endianness
        }
    }
    // Create dark matter particles
    if (newTipsy->header->ndark != 0){                                          // Check if particles exist
        newTipsy->dark = malloc(newTipsy->header->nsph*sizeof(dark_particle));  // Allocate space
        for (i=0; i < newTipsy->header->ndark; i++){
            fread(&newTipsy->dark[i].mass, sizeof(float), 9, fp);               // Read in binary
            swapEndianBatch(newTipsy, TYPE_DARK, i);                            // Swap endianness
        }
    }
    // Create star particles
    if (newTipsy->header->nstar != 0){                                          // Check if particles exist
        newTipsy->star = malloc(newTipsy->header->nsph*sizeof(star_particle));  // Allocate space
        for (i=0; i < newTipsy->header->nstar; i++){
            fread(&newTipsy->star[i].mass, sizeof(float), 11, fp);              // Read in binary
            swapEndianBatch(newTipsy, TYPE_STAR, i);                            // Swap endianness
        }
    }

// Cleanup
    fclose(fp);
// Output a pointer to the new tipsy object
    return newTipsy;
}
int writeTipsyStd(const char filename[], tipsy* tipsyOut){
    int i;
    int nsph = tipsyOut->header->nsph;
    int ndark = tipsyOut->header->ndark;
    int nstar = tipsyOut->header->nstar;

    FILE *fp = fopen(filename, "w");
// Write header


}
