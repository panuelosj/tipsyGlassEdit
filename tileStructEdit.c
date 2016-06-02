#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

/*
 ######  ########  ########    ###    ######## ########
##    ## ##     ## ##         ## ##      ##    ##
##       ##     ## ##        ##   ##     ##    ##
##       ########  ######   ##     ##    ##    ######
##       ##   ##   ##       #########    ##    ##
##    ## ##    ##  ##       ##     ##    ##    ##
 ######  ##     ## ######## ##     ##    ##    ########
 */
tipsy* tipsyCreate(const double simtime, const int nsph, const int ndark, const int nstar){
    /* Creates a new tipsy struct by allocating all relevant memory based on the
        number of particles as stated in the parameters.

        Parameters:
            const double simtime    - simulation time to be written into the header
            const int nsph          - number of gas particles to be allocated
            const int ndark         - number of dark particles to be allocated
            const int nstar         - number os star particles to be allocated
    */

    // Create object (pointer to a struct of pointers to memory)
    tipsy* tipsyOut = malloc(sizeof(tipsy));

    // Allocate and create header
    tipsyOut->header = malloc(sizeof(header));
    tipsyOut->header->simtime = simtime;
    tipsyOut->header->nbodies = nsph + ndark + nstar;
    tipsyOut->header->ndim = 3;
    tipsyOut->header->nsph = nsph;
    tipsyOut->header->ndark = ndark;
    tipsyOut->header->nstar = nstar;
    tipsyOut->header->pad = 0;

    // Allocate space for particles
    if (tipsyOut->header->nsph != 0){
        tipsyOut->gas = malloc(tipsyOut->header->nsph*sizeof(gas_particle));
    } else tipsyOut->gas = NULL;
    if (tipsyOut->header->ndark != 0){
        tipsyOut->dark = malloc(tipsyOut->header->ndark*sizeof(dark_particle));
    } else tipsyOut->dark = NULL;
    if (tipsyOut->header->nstar != 0){
        tipsyOut->star = malloc(tipsyOut->header->nstar*sizeof(star_particle));
    } else tipsyOut->star = NULL;

    // Allocate and define object attributes
    tipsyOut->attr = malloc(sizeof(attributes));
    tipsyOut->attr->nloadedsph = 0;
    tipsyOut->attr->nloadeddark = 0;
    tipsyOut->attr->nloadedstar = 0;

    return tipsyOut;
}

/*
########  ########  ######  ######## ########   #######  ##    ##
##     ## ##       ##    ##    ##    ##     ## ##     ##  ##  ##
##     ## ##       ##          ##    ##     ## ##     ##   ####
##     ## ######    ######     ##    ########  ##     ##    ##
##     ## ##             ##    ##    ##   ##   ##     ##    ##
##     ## ##       ##    ##    ##    ##    ##  ##     ##    ##
########  ########  ######     ##    ##     ##  #######     ##
*/
void tipsyDestroy(tipsy* tipsyIn){
    /* Frees the memory allocated to the input tipsy file

        Parameters:
            tipsy* tipsyIn      - pointer to the tipsy struct to deallocate
    */
    // First deallocate all structs inside the tipsy struct
    free(tipsyIn->header);
    free(tipsyIn->gas);
    free(tipsyIn->dark);
    free(tipsyIn->star);
    free(tipsyIn->attr);
    // and deallocate the full tipsy struct
    free(tipsyIn);
}

/*
 ######   ##        #######  ##    ## ########
##    ##  ##       ##     ## ###   ## ##
##        ##       ##     ## ####  ## ##
##        ##       ##     ## ## ## ## ######
##        ##       ##     ## ##  #### ##
##    ##  ##       ##     ## ##   ### ##
 ######   ########  #######  ##    ## ########
*/
tipsy* tipsyClone(tipsy* tipsyIn){
    /* Copies the input tipsy file into a new tipsy struct and returns a pointer
        to the newly created tipsy struct. createTipsy() does not need to be
        called beforehand, it is called within this function to create the
        tipsy struct.

        Parameters:
            tipsy* tipsyIn      - pointer to the tipsy struct to be cloned
        Return:
            pointer to the newly created tipsy struct with values identical
            to the input tipsy
    */

    // Indexing Variables
    int i;
    // Create new tipsy object
    tipsy* tipsyOut = tipsyCreate(tipsyIn->header->simtime, tipsyIn->header->nsph, tipsyIn->header->ndark, tipsyIn->header->nstar);
    // Copy header, gas, dark, and star particles, and attributes
    memcpy(tipsyOut->header, tipsyIn->header, sizeof(header));
    memcpy(tipsyOut->gas, tipsyIn->gas, tipsyIn->header->nsph * sizeof(gas_particle));
    memcpy(tipsyOut->dark, tipsyIn->dark, tipsyIn->header->ndark * sizeof(dark_particle));
    memcpy(tipsyOut->star, tipsyIn->star, tipsyIn->header->nstar * sizeof(star_particle));
    memcpy(tipsyOut->attr, tipsyIn->attr, sizeof(attributes));

    // Return pointer to new tipsy struct with the same values as the input struct
    return tipsyOut;
}

/*
######## ##     ## ######## ######## ##    ## ########
##        ##   ##     ##    ##       ###   ## ##     ##
##         ## ##      ##    ##       ####  ## ##     ##
######      ###       ##    ######   ## ## ## ##     ##
##         ## ##      ##    ##       ##  #### ##     ##
##        ##   ##     ##    ##       ##   ### ##     ##
######## ##     ##    ##    ######## ##    ## ########
*/
void tipsyExtend(tipsy* tipsyIn, const int nNewSPH, const int nNewDark, const int nNewStar){
    /* Uses realloc() to extend the size of the memory spaces holding SPH, dark
        and star particles. Will print a warning if the new size provided is
        smaller than the current size, but will proceed as usual, shrinking the
        available memory. If more particles are loaded, particle data will be
        lost. Header values are updated but nloaded are only updated when data
        is known to be lost. On size increase, nloaded is unchanged since any
        new particle data are left uninitialized.

        Parameters:
            tipsy* tipsyIn      - pointer to the tipsy requiring more space
            const int nNewSPH   - new number of SPH particles
            const int nNewDark  - new number of dark particles
            const int nNewStar  - new number of star particles

        ToDo: Add error checking on realloc to check if a larger memory space
            was found; Add better updates to nloaded to count in case particle
            array has gaps;
    */

    // Print warnings if new sizes are smaller than current sizes
    if ((nNewSPH < tipsyIn->attr->nloadedsph) || (nNewDark < tipsyIn->attr->nloadeddark) || (nNewStar < tipsyIn->attr->nloadedstar))
        warnCase(WARN_REALLOC_DATA_LOSS);
    else if ((nNewSPH < tipsyIn->header->nsph) || (nNewDark < tipsyIn->header->ndark) || (nNewStar < tipsyIn->header->nstar))
        warnCase(WARN_REALLOC_SHRINK);

    // Do reallocations
    tipsyIn->gas = realloc(tipsyIn->gas, nNewSPH*sizeof(gas_particle));
    tipsyIn->dark = realloc(tipsyIn->dark, nNewDark*sizeof(dark_particle));
    tipsyIn->star = realloc(tipsyIn->star, nNewStar*sizeof(star_particle));

    // Change size in header
    tipsyIn->header->nsph = nNewSPH;
    tipsyIn->header->ndark = nNewDark;
    tipsyIn->header->nstar = nNewStar;
    tipsyIn->header->nbodies = nNewSPH + nNewDark + nNewStar;
    // nloaded values in attr are changed only when data is known to be lost
    if (tipsyIn->attr->nloadedsph > tipsyIn->header->nsph)
        tipsyIn->attr->nloadedsph = tipsyIn->header->nsph;
    if (tipsyIn->attr->nloadeddark > tipsyIn->header->ndark)
        tipsyIn->attr->nloadeddark = tipsyIn->header->ndark;
    if (tipsyIn->attr->nloadedstar > tipsyIn->header->nstar)
        tipsyIn->attr->nloadedstar = tipsyIn->header->nstar;
}
