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
    // Allocate space
    newTipsy->header = malloc(sizeof(header));
    // Read in binary
    fread(&newTipsy->header->simtime, sizeof(double), 1, fp);
    fread(&newTipsy->header->nbodies, sizeof(int), 6, fp);
    // Swap endianness
    newTipsy->header->simtime = swapEndianDouble(newTipsy->header->simtime);
    newTipsy->header->nbodies = swapEndianInt(newTipsy->header->nbodies);
    newTipsy->header->ndim = swapEndianInt(newTipsy->header->ndim);
    newTipsy->header->nsph = swapEndianInt(newTipsy->header->nsph);
    newTipsy->header->ndark = swapEndianInt(newTipsy->header->ndark);
    newTipsy->header->nstar = swapEndianInt(newTipsy->header->nstar);

// Create gas particles
    // Check if particles exist
    if (newTipsy->header->nsph != 0){
        // Allocate space
        newTipsy->gas = malloc(newTipsy->header->nsph*sizeof(gas_particle));
        for (i=0; i < newTipsy->header->nsph; i++){
            // Read in binary
            fread(&newTipsy->gas[i].mass, sizeof(float), 12, fp);
            // Swap endianness
            newTipsy->gas[i].mass = swapEndianFloat(newTipsy->gas[i].mass);
            newTipsy->gas[i].pos[0] = swapEndianFloat(newTipsy->gas[i].pos[0]);
            newTipsy->gas[i].pos[1] = swapEndianFloat(newTipsy->gas[i].pos[1]);
            newTipsy->gas[i].pos[2] = swapEndianFloat(newTipsy->gas[i].pos[2]);
            newTipsy->gas[i].vel[0] = swapEndianFloat(newTipsy->gas[i].vel[0]);
            newTipsy->gas[i].vel[1] = swapEndianFloat(newTipsy->gas[i].vel[1]);
            newTipsy->gas[i].vel[2] = swapEndianFloat(newTipsy->gas[i].vel[2]);
            newTipsy->gas[i].rho = swapEndianFloat(newTipsy->gas[i].rho);
            newTipsy->gas[i].temp = swapEndianFloat(newTipsy->gas[i].temp);
            newTipsy->gas[i].eps = swapEndianFloat(newTipsy->gas[i].eps);
            newTipsy->gas[i].metals = swapEndianFloat(newTipsy->gas[i].metals);
            newTipsy->gas[i].phi = swapEndianFloat(newTipsy->gas[i].phi);
        }
    }

// Create dark matter particles
    // Check if particles exist
    if (newTipsy->header->ndark != 0){
        // Allocate space
        newTipsy->dark = malloc(newTipsy->header->nsph*sizeof(dark_particle));
        for (i=0; i < newTipsy->header->ndark; i++){
            // Read in binary
            fread(&newTipsy->dark[i].mass, sizeof(float), 9, fp);
            // Swap endianness
            newTipsy->dark[i].mass = swapEndianFloat(newTipsy->dark[i].mass);
            newTipsy->dark[i].pos[0] = swapEndianFloat(newTipsy->dark[i].pos[0]);
            newTipsy->dark[i].pos[1] = swapEndianFloat(newTipsy->dark[i].pos[1]);
            newTipsy->dark[i].pos[2] = swapEndianFloat(newTipsy->dark[i].pos[2]);
            newTipsy->dark[i].vel[0] = swapEndianFloat(newTipsy->dark[i].vel[0]);
            newTipsy->dark[i].vel[1] = swapEndianFloat(newTipsy->dark[i].vel[1]);
            newTipsy->dark[i].vel[2] = swapEndianFloat(newTipsy->dark[i].vel[2]);
            newTipsy->dark[i].eps = swapEndianFloat(newTipsy->dark[i].eps);
            newTipsy->dark[i].phi = swapEndianFloat(newTipsy->dark[i].phi);
        }
    }

// Create star particles
    // Check if particles exist
    if (newTipsy->header->nstar != 0){
        // Allocate space
        newTipsy->star = malloc(newTipsy->header->nsph*sizeof(star_particle));
        for (i=0; i < newTipsy->header->nstar; i++){
            // Read in binary
            fread(&newTipsy->star[i].mass, sizeof(float), 11, fp);
            // Swap endianness
            newTipsy->star[i].mass = swapEndianFloat(newTipsy->star[i].mass);
            newTipsy->star[i].pos[0] = swapEndianFloat(newTipsy->star[i].pos[0]);
            newTipsy->star[i].pos[1] = swapEndianFloat(newTipsy->star[i].pos[1]);
            newTipsy->star[i].pos[2] = swapEndianFloat(newTipsy->star[i].pos[2]);
            newTipsy->star[i].vel[0] = swapEndianFloat(newTipsy->star[i].vel[0]);
            newTipsy->star[i].vel[1] = swapEndianFloat(newTipsy->star[i].vel[1]);
            newTipsy->star[i].vel[2] = swapEndianFloat(newTipsy->star[i].vel[2]);
            newTipsy->star[i].metals = swapEndianFloat(newTipsy->star[i].metals);
            newTipsy->star[i].tform = swapEndianFloat(newTipsy->star[i].tform);
            newTipsy->star[i].eps = swapEndianFloat(newTipsy->star[i].eps);
            newTipsy->star[i].phi = swapEndianFloat(newTipsy->star[i].phi);
        }
    }

// Cleanup
    fclose(fp);
// Output a pointer to the new tipsy object
    return newTipsy;
}

int writeTipsyStd(const char filename[], tipsy* tipsyOut){
    int i;
    int nsph, ndark, nstar;

    FILE *fp = fopen(filename, "w");

// Write header


}
