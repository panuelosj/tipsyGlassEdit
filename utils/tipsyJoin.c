#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../tile.h"

int main(int argc, char *argv[]){
    if (argc != 4) {
        system("cat nagato");
        printf("Error: not enough arguments\n");
        printf("Usage:\n\t %s [fileIn1] [fileIn2] [fileOut] \n", argv[0]);
        exit(-1);
        //errorCase(ERR_MISSING_ARGS);                                            //errorCase() automatically exits the program
    }
    // Read in the input glass, filename as given in main's argument
    printf("Reading: %s\n", argv[1]);
    tipsy* tipsyIn1 = readTipsyStd(argv[1]);
    printHeader(tipsyIn1->head);
    printAttr(tipsyIn1->attr);
    printf("=================================================\n");

    printf("Reading: %s\n", argv[2]);
    tipsy* tipsyIn2 = readTipsyStd(argv[2]);
    printHeader(tipsyIn2->head);
    printAttr(tipsyIn2->attr);
    printf("=================================================\n");

    tipsy* tipsyOut = tipsyJoin(tipsyIn1, tipsyIn2);
    printf("Writing to: %s\n", argv[3]);
    writeTipsyStd(argv[3], tipsyOut);
    printHeader(tipsyOut->head);
    printAttr(tipsyOut->attr);

    // Cleanup
    tipsyDestroy(tipsyIn1);
    tipsyDestroy(tipsyIn2);
    tipsyDestroy(tipsyOut);
}
