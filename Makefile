SHARED_OBJ = shared/tileCalc.o shared/tileStructEdit.o shared/tileFileIO.o shared/tileUtils.o shared/tileMisc.o

tile: tile.o $(SHARED_OBJ) tile.h
	gcc -o tile tile.o $(SHARED_OBJ)

# Random Utils
tipsyPrintRho: utils/tipsyPrintRho.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyPrintRho utils/tipsyPrintRho.o $(SHARED_OBJ)

tipsyPrintRho.o: utils/tipsyPrintRho.c tile.h
	gcc -c utils/tipsyPrintRho.c

# Functions
tile.o: tile.c tile.h
	gcc -c tile.c

tileCalc.o: shared/tileCalc.c tile.h
	gcc -c shared/tileCalc.c

tileStructEdit.o: shared/tileStructEdit.c tile.h
	gcc -c shared/tileStructEdit.c

tileFileIO.o: shared/tileFileIO.c tile.h
	gcc -c shared/tileFileIO.c

tileUtils.o: shared/tileUtils.c tile.h
	gcc -c shared/tileUtils.c

tileMisc.o: shared/tileMisc.c tile.h
	gcc -c shared/tileMisc.c
