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

        ToDo:
            - Add error checking on realloc to check if a larger memory space
            was found
            - Add better updates to nloaded to count in case particle
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

/*
      ##  #######  #### ##    ##
      ## ##     ##  ##  ###   ##
      ## ##     ##  ##  ####  ##
      ## ##     ##  ##  ## ## ##
##    ## ##     ##  ##  ##  ####
##    ## ##     ##  ##  ##   ###
 ######   #######  #### ##    ##
*/
tipsy* tipsyJoin(tipsy* tipsy1, tipsy* tipsy2){
    /* Creates a new tipsy object, taking the union of the two input tipsy
        objects. This is done be cloning the first tipsy input, then extending
        the clone, and adding the data for the second tipsy input. This means
        that the larger object should always be placed in first, for better
        performance.

        Parameters:
            tipsy* tipsy1, tipsy2   - tipsy objects to take the union of

        ToDo:
            - add check to see if the input tipsies are full. Program currently
                assumes the input files are full (uses n_ not nloaded_) and
                copies them directly, even if some particle values are
                unitialized
    */

    int i;                                                                      // indexing variables
    const int nsph = tipsy1->header->nsph + tipsy2->header->nsph;
    const int ndark = tipsy1->header->ndark + tipsy2->header->ndark;
    const int nstar = tipsy1->header->nstar + tipsy2->header->nstar;

    // clone the first tipsy object (inputs the values)
    tipsy* tipsyOut = tipsyClone(tipsy1);
    // extend the clone to fit in the values from the second object
    tipsyExtend(tipsyOut, nsph, ndark, nstar);
    // copy the second object's values
    memcpy(&tipsyOut->gas[tipsy1->header->nsph], &tipsy2->gas[0], tipsy2->header->nsph*sizeof(gas_particle));
    memcpy(&tipsyOut->dark[tipsy1->header->ndark], &tipsy2->dark[0], tipsy2->header->ndark*sizeof(dark_particle));
    memcpy(&tipsyOut->star[tipsy1->header->nstar], &tipsy2->star[0], tipsy2->header->nstar*sizeof(star_particle));

    // update header values
    tipsyOut->header->nsph = nsph;
    tipsyOut->header->ndark = ndark;
    tipsyOut->header->nstar = nstar;
    tipsyOut->header->nbodies = nsph+ndark+nstar;
    // update attributes, current attributes were inherited from tipsy1 when cloned
    if (tipsy2->attr->xmin < tipsyOut->attr->xmin)
        tipsyOut->attr->xmin = tipsy2->attr->xmin;
    if (tipsy2->attr->xmax > tipsyOut->attr->xmax)
        tipsyOut->attr->xmax = tipsy2->attr->xmax;
    if (tipsy2->attr->ymin < tipsyOut->attr->ymin)
        tipsyOut->attr->ymin = tipsy2->attr->ymin;
    if (tipsy2->attr->ymax > tipsyOut->attr->ymax)
        tipsyOut->attr->ymax = tipsy2->attr->ymax;
    if (tipsy2->attr->zmin < tipsyOut->attr->zmin)
        tipsyOut->attr->zmin = tipsy2->attr->zmin;
    if (tipsy2->attr->zmax > tipsyOut->attr->zmax)
        tipsyOut->attr->zmax = tipsy2->attr->zmax;

    return tipsyOut;
}
