#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../tipsyEdit.h"

int main(int argc, char *argv[]){
    if (argc != 6) {
        system("cat nagato");
        printf("Error: not enough arguments\n");
        printf("Usage:\n\t %s [fileIn] [fileOut] [xExpand] [yExpand] [zExpand]\n", argv[0]);
        exit(-1);
        //errorCase(ERR_MISSING_ARGS);                                            //errorCase() automatically exits the program
    }
    // Read in the input glass, filename as given in main's argument
    printf("Reading: %s\n", argv[1]);
    tipsy* tipsyIn = readTipsyStd(argv[1]);
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);
    printf("=================================================\n");

    tipsyScaleExpand(tipsyIn,
                    (int)strtol(argv[3], NULL, 10),
                    (int)strtol(argv[4], NULL, 10),
                    (int)strtol(argv[5], NULL, 10));
    printf("Writing to: %s\n", argv[2]);
    writeTipsyStd(argv[2], tipsyIn);
    printHeader(tipsyIn->head);
    printAttr(tipsyIn->attr);

    // Cleanup
    tipsyDestroy(tipsyIn);
}
