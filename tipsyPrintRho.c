#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tile.h"

int main(int argc, char *argv[]){
    // Indexing Variables
    int i,j;
    // Read in the input glass, filename as given in main's argument
    printf("Reading: %s\n", argv[1]);
    tipsy* glassIn = readTipsyStd(argv[1]);
    printf("Input ");
    printHeader(glassIn->header);
    printAttr(glassIn->attr);
    printf("=================================================\n");

    for(i=0; i < glassIn->header->nsph; i++){
        for(j=0; j<10; j++){
            printf("%f, ", glassIn->gas[i].rho);
        }
        printf("\n");
    }
    // Cleanup
    tipsyDestroy(glassIn);
}
