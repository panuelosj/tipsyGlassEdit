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
    // Indexing Variables
    int i;
    // Create object (pointer to a struct of pointers to memory)
    tipsy* tipsyOut = malloc(sizeof(tipsy));
    // Define object properties
    // Allocate and create header
    tipsyOut->header = malloc(sizeof(header));
    tipsyOut->header->simtime = simtime;
    tipsyOut->header->nbodies = nsph + ndark + nstar;
    tipsyOut->header->ndim = 3;
    tipsyOut->header->nsph = nsph;
    tipsyOut->header->ndark = ndark;
    tipsyOut->header->nstar = nstar;
    tipsyOut->header->pad = 0;
    // Allocate space for gas particles and set default values
    if (tipsyOut->header->nsph != 0){
        tipsyOut->gas = malloc(tipsyOut->header->nsph*sizeof(gas_particle));
        for (i=0; i < tipsyOut->header->nsph; i++){
            tipsyOut->gas[i].mass = 1.0;
            tipsyOut->gas[i].pos[AXIS_X] = VAL_NaN;
            tipsyOut->gas[i].pos[AXIS_Y] = VAL_NaN;
            tipsyOut->gas[i].pos[AXIS_Z] = VAL_NaN;
            tipsyOut->gas[i].vel[AXIS_X] = 0.0;
            tipsyOut->gas[i].vel[AXIS_Y] = 0.0;
            tipsyOut->gas[i].vel[AXIS_Z] = 0.0;
            tipsyOut->gas[i].rho = 1.0;
            tipsyOut->gas[i].temp = 1.0;
            tipsyOut->gas[i].eps = 1.0;
            tipsyOut->gas[i].metals = 0.0;
            tipsyOut->gas[i].phi = 1.0;
        }
    } else tipsyOut->gas = NULL;
    // Allocate space for dark particles and set default values
    if (tipsyOut->header->ndark != 0){
        tipsyOut->dark = malloc(tipsyOut->header->ndark*sizeof(dark_particle));
        for (i=0; i < tipsyOut->header->ndark; i++){
            tipsyOut->dark[i].mass = 1.0;
            tipsyOut->dark[i].pos[AXIS_X] = VAL_NaN;
            tipsyOut->dark[i].pos[AXIS_Y] = VAL_NaN;
            tipsyOut->dark[i].pos[AXIS_Z] = VAL_NaN;
            tipsyOut->dark[i].vel[AXIS_X] = 0.0;
            tipsyOut->dark[i].vel[AXIS_Y] = 0.0;
            tipsyOut->dark[i].vel[AXIS_Z] = 0.0;
            tipsyOut->dark[i].eps = 1.0;
            tipsyOut->dark[i].phi = 1.0;
        }
    } else tipsyOut->dark = NULL;
    // Allocate space for star particles and set default values
    if (tipsyOut->header->nstar != 0){
        tipsyOut->star = malloc(tipsyOut->header->nstar*sizeof(star_particle));
        for (i=0; i < tipsyOut->header->nstar; i++){
            tipsyOut->star[i].mass = 1.0;
            tipsyOut->star[i].pos[AXIS_X] = VAL_NaN;
            tipsyOut->star[i].pos[AXIS_Y] = VAL_NaN;
            tipsyOut->star[i].pos[AXIS_Z] = VAL_NaN;
            tipsyOut->star[i].vel[AXIS_X] = 0.0;
            tipsyOut->star[i].vel[AXIS_Y] = 0.0;
            tipsyOut->star[i].vel[AXIS_Z] = 0.0;
            tipsyOut->star[i].metals = 0.0;
            tipsyOut->star[i].tform = 0.0;
            tipsyOut->star[i].eps = 1.0;
            tipsyOut->star[i].phi = 1.0;
        }
    } else tipsyOut->star = NULL;
    // Allocate space for attributes and set default values
    tipsyOut->attr = malloc(sizeof(attributes));
    tipsyOut->attr->nloadedsph = 0;
    tipsyOut->attr->nloadeddark = 0;
    tipsyOut->attr->nloadedstar = 0;


    return tipsyOut;
}


tipsy* tipsyClone(tipsy* tipsyIn){
    /* Copies the input tipsy file into a new tipsy struct and returns a pointer
        to the newly created tipsy struct.

        Parameters:
            tipsy* tipsyIn      - pointer to the tipsy struct to be cloned
        Return:
            pointer to the newly created tipsy struct with values identical
            to the input tipsy
    */

    // Indexing Variables
    int i;
    // Create new tipsy object
    tipsy* tipsyOut = createTipsy(tipsyIn->header->simtime, tipsyIn->header->nsph, tipsyIn->header->ndark, tipsyIn->header->nstar);
    // Copy header, gas, dark, and star particles, and attributes
    memcpy(tipsyOut->header, tipsyIn->header, sizeof(header));
    memcpy(tipsyOut->gas, tipsyIn->gas, tipsyIn->header->nsph * sizeof(gas_particle));
    memcpy(tipsyOut->dark, tipsyIn->dark, tipsyIn->header->ndark * sizeof(dark_particle));
    memcpy(tipsyOut->star, tipsyIn->star, tipsyIn->header->nstar * sizeof(star_particle));
    memcpy(tipsyOut->attr, tipsyIn->attr, sizeof(attributes));

    // Return pointer to new tipsy struct with the same values as the input struct
    return tipsyOut;
}
