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
    char filename[100] = "glass16.std";
    printf("Reading: %s\n", filename);
    tipsy* glassIn = readTipsyStd(filename);

    glassIn->attr->xmin = -0.5; glassIn->attr->xmax = 0.5;
    glassIn->attr->ymin = -0.5; glassIn->attr->ymax = 0.5;
    glassIn->attr->zmin = -0.5; glassIn->attr->zmax = 0.5;

    printHeader(glassIn->header);


    printf("p0:\n");
    printGas(&glassIn->gas[0]);
    tipsy* compressed = tipsyCompress(glassIn, 2, 3, 1);
    printGas(&compressed->gas[0]);
    printf("%f-%f, %f-%f, %f-%f\n", compressed->attr->xmin, compressed->attr->xmax, compressed->attr->ymin, compressed->attr->ymax, compressed->attr->zmin, compressed->attr->zmax);
    writeTipsyStd("glass16.std.cpy", compressed);
}

void printGas(gas_particle* p){
    printf("\tmass:\t%f\n", p->mass);
    printf("\tpos:\t%f, %f, %f\n", p->pos[0], p->pos[1], p->pos[2]);
    printf("\tvel:\t%f, %f, %f\n", p->vel[0], p->vel[1], p->vel[2]);
    printf("\trho:\t%f\n\ttemp:\t%f\n\teps:\t%f\n\tmetals:\t%f\n\tphi:\t%f\n", p->rho,p->temp,p->eps,p->metals,p->phi);
}
void printHeader(header* h){
    printf("Header:\n");
    printf("\tsimtime:\t%f\n\tnbodies:\t%i\n\tndim:\t%i\n\tnsph:\t%i\n\tndark:\t%i\n\tnstar:\t%i\n\tpad:\t%i\n",
            h->simtime, h->nbodies, h->ndim, h->nsph, h->ndark, h->nstar, h->pad);
    //printf("Float: %i, Int: %i, Double: %i\n", sizeof(float), sizeof(int), sizeof(double));
}
