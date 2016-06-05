#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../tile.h"

int main(int argc, char *argv[]){
    if (argc != 3) {
        system("cat nagato");
        printf("Error: not enough arguments\n");
        printf("Usage:\n\t %s [fileIn] [fileOut]\n", argv[0]);
        exit(-1);
        //errorCase(ERR_MISSING_ARGS);                                            //errorCase() automatically exits the program
    }
    // Read in the input tipsy, filename as given in main's argument
    printf("Reading: %s\n", argv[1]);
    tipsy* tipsyIn = readTipsyStd(argv[1]);
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);
    printf("=================================================\n");

    tipsyCenter(tipsyIn);
    printf("Writing to: %s\n", argv[2]);
    writeTipsyStd(argv[2], tipsyIn);
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);

    // Cleanup
    tipsyDestroy(tipsyIn);
}
