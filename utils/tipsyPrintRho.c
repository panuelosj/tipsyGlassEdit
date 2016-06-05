#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../tipsyEdit.h"

int main(int argc, char *argv[]){
    if (argc != 2){
        system("cat nagato");
        printf("Error: not enough arguments\n");
        printf("Usage:\n\t %s [fileIn]", argv[0]);
        exit(-1);
        //errorCase(ERR_MISSING_ARGS);                                            //errorCase() automatically exits the program
    }
    // Indexing Variables
    int i,j;
    // Read in the input tipsy, filename as given in main's argument
    printf("Reading: %s\n", argv[1]);
    tipsy* tipsyIn = readTipsyStd(argv[1]);
    printf("Input ");
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);
    printf("=================================================\n");

    for(i=0; i < tipsyIn->head->nsph; i++){
        for(j=0; j<10; j++){
            printf("%f, ", tipsyIn->gas[i].rho);
        }
        printf("\n");
    }
    // Cleanup
    tipsyDestroy(tipsyIn);
}
