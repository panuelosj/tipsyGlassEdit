SHARED_OBJ = shared/tileCalc.o shared/tileStructEdit.o shared/tileFileIO.o shared/tileUtils.o shared/tileMisc.o

tile: tile.o $(SHARED_OBJ) tile.h
	gcc -o tile tile.o $(SHARED_OBJ)

utils: tipsyPrintRho tipsyCenter tipsyShrink tipsyExpand tipsyTesselate tipsyTranslate tipsyJoin

# Random Utils
tipsyPrintRho: utils/tipsyPrintRho.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyPrintRho utils/tipsyPrintRho.o $(SHARED_OBJ)

tipsyPrintRho.o: utils/tipsyPrintRho.c tile.h
	gcc -c utils/tipsyPrintRho.c

tipsyCenter: utils/tipsyCenter.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyCenter utils/tipsyCenter.o $(SHARED_OBJ)

tipsyCenter.o: utils/tipsyCenter.c tile.h
	gcc -c utils/tipsyCenter.c

tipsyShrink: utils/tipsyShrink.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyShrink utils/tipsyShrink.o $(SHARED_OBJ)

tipsyShrink.o: utils/tipsyShrink.c tile.h
	gcc -c utils/tipsyShrink.c

tipsyExpand: utils/tipsyExpand.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyExpand utils/tipsyExpand.o $(SHARED_OBJ)

tipsyExpand.o: utils/tipsyExpand.c tile.h
	gcc -c utils/tipsyExpand.c

tipsyTesselate: utils/tipsyTesselate.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyTesselate utils/tipsyTesselate.o $(SHARED_OBJ)

tipsyTesselate.o: utils/tipsyTesselate.c tile.h
	gcc -c utils/tipsyTesselate.c

tipsyTranslate: utils/tipsyTranslate.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyTranslate utils/tipsyTranslate.o $(SHARED_OBJ)

tipsyTranslate.o: utils/tipsyTranslate.c tile.h
	gcc -c utils/tipsyTranslate.c

tipsyJoin: utils/tipsyJoin.o $(SHARED_OBJ) tile.h
	gcc -o utils/tipsyJoin utils/tipsyJoin.o $(SHARED_OBJ)

tipsyJoin.o: utils/tipsyJoin.c tile.h
	gcc -c utils/tipsyJoin.c

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
