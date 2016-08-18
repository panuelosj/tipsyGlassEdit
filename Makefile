SHARED_OBJ = shared/tipsyEditCalc.o shared/tipsyEditStructUtils.o shared/tipsyEditFileIO.o shared/tipsyEditUtils.o shared/tipsyEditMisc.o shared/particleFlops.o

tipsyEdit: tipsyEdit.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o tipsyEdit tipsyEdit.o $(SHARED_OBJ) -lm

utils: tipsyPrintRho tipsyPrintVel tipsyPrintHeader tipsyCenter tipsyShrink tipsyExpand tipsyTesselate tipsyTranslate tipsyJoin

# Random Utils
tipsyPrintRho: utils/tipsyPrintRho.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyPrintRho utils/tipsyPrintRho.o $(SHARED_OBJ)

tipsyPrintRho.o: utils/tipsyPrintRho.c tipsyEdit.h
	gcc -c utils/tipsyPrintRho.c

tipsyPrintVel: utils/tipsyPrintVel.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyPrintVel utils/tipsyPrintVel.o $(SHARED_OBJ)

tipsyPrintVel.o: utils/tipsyPrintVel.c tipsyEdit.h
	gcc -c utils/tipsyPrintVel.c

tipsyPrintHeader: utils/tipsyPrintHeader.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyPrintHeader utils/tipsyPrintHeader.o $(SHARED_OBJ)

tipsyPrintHeader.o: utils/tipsyPrintHeader.c tipsyEdit.h
	gcc -c utils/tipsyPrintHeader.c

tipsyCenter: utils/tipsyCenter.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyCenter utils/tipsyCenter.o $(SHARED_OBJ)

tipsyCenter.o: utils/tipsyCenter.c tipsyEdit.h
	gcc -c utils/tipsyCenter.c

tipsyShrink: utils/tipsyShrink.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyShrink utils/tipsyShrink.o $(SHARED_OBJ)

tipsyShrink.o: utils/tipsyShrink.c tipsyEdit.h
	gcc -c utils/tipsyShrink.c

tipsyExpand: utils/tipsyExpand.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyExpand utils/tipsyExpand.o $(SHARED_OBJ)

tipsyExpand.o: utils/tipsyExpand.c tipsyEdit.h
	gcc -c utils/tipsyExpand.c

tipsyTesselate: utils/tipsyTesselate.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyTesselate utils/tipsyTesselate.o $(SHARED_OBJ)

tipsyTesselate.o: utils/tipsyTesselate.c tipsyEdit.h
	gcc -c utils/tipsyTesselate.c

tipsyTranslate: utils/tipsyTranslate.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyTranslate utils/tipsyTranslate.o $(SHARED_OBJ)

tipsyTranslate.o: utils/tipsyTranslate.c tipsyEdit.h
	gcc -c utils/tipsyTranslate.c

tipsyJoin: utils/tipsyJoin.o $(SHARED_OBJ) tipsyEdit.h
	gcc -o utils/tipsyJoin utils/tipsyJoin.o $(SHARED_OBJ)

tipsyJoin.o: utils/tipsyJoin.c tipsyEdit.h
	gcc -c utils/tipsyJoin.c

# Functions
tipsyEdit.o: tipsyEdit.c tipsyEdit.h
	gcc -c tipsyEdit.c -lm

tipsyEditCalc.o: shared/tipsyEditCalc.c tipsyEdit.h
	gcc -c shared/tipsyEditCalc.c

tipsyEditStructUtils.o: shared/tipsyEditStructUtils.c tipsyEdit.h
	gcc -c shared/tipsyEditStructUtils.c

tipsyEditFileIO.o: shared/tipsyEditFileIO.c tipsyEdit.h
	gcc -c shared/tipsyEditFileIO.c

tipsyEditUtils.o: shared/tipsyEditUtils.c tipsyEdit.h
	gcc -c shared/tipsyEditUtils.c

tipsyEditMisc.o: shared/tipsyEditMisc.c tipsyEdit.h
	gcc -c shared/tipsyEditMisc.c

particleFlops.o: shared/particleFlops.c tipsyEdit.h
	gcc -c shared/particleFlops.c
