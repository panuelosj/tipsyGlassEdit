#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

//=============================================================================
//-------------------------READ AND WRITE--------------------------------------
//=============================================================================

tipsy* readTipsyStd(const char filename[]){
    int i;

    FILE *fp = fopen(filename, "r");
    // Create object
    tipsy* newTipsy = malloc(sizeof(tipsy));

    // Create and read in header
    newTipsy->header = malloc(sizeof(header));                                  // Allocate space
    fread(&newTipsy->header->simtime, sizeof(double), 1, fp);                   // Read in binary
    fread(&newTipsy->header->nbodies, sizeof(int), 6, fp);
    swapEndianBatch(newTipsy, TYPE_HEADER, 0);                                  // Swap endianness
    // Create and read in gas particles
    if (newTipsy->header->nsph != 0){                                           // Check if particles exist
        newTipsy->gas = malloc(newTipsy->header->nsph*sizeof(gas_particle));    // Allocate space
        for (i=0; i < newTipsy->header->nsph; i++){
            fread(&newTipsy->gas[i].mass, sizeof(float), 12, fp);               // Read in binary
            swapEndianBatch(newTipsy, TYPE_GAS, i);                             // Swap endianness
        }
    } else newTipsy->gas = NULL;
    // Create and read in dark matter particles
    if (newTipsy->header->ndark != 0){                                          // Check if particles exist
        newTipsy->dark = malloc(newTipsy->header->nsph*sizeof(dark_particle));  // Allocate space
        for (i=0; i < newTipsy->header->ndark; i++){
            fread(&newTipsy->dark[i].mass, sizeof(float), 9, fp);               // Read in binary
            swapEndianBatch(newTipsy, TYPE_DARK, i);                            // Swap endianness
        }
    } else newTipsy->dark = NULL;
    // Create and read in star particles
    if (newTipsy->header->nstar != 0){                                          // Check if particles exist
        newTipsy->star = malloc(newTipsy->header->nsph*sizeof(star_particle));  // Allocate space
        for (i=0; i < newTipsy->header->nstar; i++){
            fread(&newTipsy->star[i].mass, sizeof(float), 11, fp);              // Read in binary
            swapEndianBatch(newTipsy, TYPE_STAR, i);                            // Swap endianness
        }
    } else newTipsy->star = NULL;

    // Create and set attributes
    newTipsy->attr = malloc(sizeof(attributes));
    newTipsy->attr->nloadedsph = newTipsy->header->nsph;
    newTipsy->attr->nloadeddark = newTipsy->header->ndark;
    newTipsy->attr->nloadedstar = newTipsy->header->nstar;
    autoFindBounds(newTipsy);

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
    swapEndianBatch(tipsyOut, TYPE_HEADER, 0);                                  // Swap to .std endianness
    fwrite(&tipsyOut->header->simtime, sizeof(double), 1, fp);                  // Write to binary
    fwrite(&tipsyOut->header->nbodies, sizeof(int), 6, fp);
    swapEndianBatch(tipsyOut, TYPE_HEADER, 0);                                  // Return to working in machine endianness
    // Write gas particles
    if (tipsyOut->header->nsph != 0){
        for (i=0; i < tipsyOut->header->nsph; i++){
            swapEndianBatch(tipsyOut, TYPE_GAS, i);                             // Swap to .std endianness
            fwrite(&tipsyOut->gas[i].mass, sizeof(float), 12, fp);              // Write to binary
            swapEndianBatch(tipsyOut, TYPE_GAS, i);                             // Return to working in machine endianness
        }
    }
    // Write dark matter particles
    if (tipsyOut->header->ndark != 0){
        for (i=0; i < tipsyOut->header->ndark; i++){
            swapEndianBatch(tipsyOut, TYPE_DARK, i);                             // Swap to .std endianness
            fwrite(&tipsyOut->dark[i].mass, sizeof(float), 9, fp);              // Write to binary
            swapEndianBatch(tipsyOut, TYPE_DARK, i);                             // Return to working in machine endianness
        }
    }
    // Write gas particles
    if (tipsyOut->header->nstar != 0){
        for (i=0; i < tipsyOut->header->nstar; i++){
            swapEndianBatch(tipsyOut, TYPE_STAR, i);                             // Swap to .std endianness
            fwrite(&tipsyOut->star[i].mass, sizeof(float), 12, fp);              // Write to binary
            swapEndianBatch(tipsyOut, TYPE_STAR, i);                             // Return to working in machine endianness
        }
    }

    // Cleanup
    fclose(fp);
}
