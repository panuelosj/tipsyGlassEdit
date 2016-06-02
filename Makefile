tile: tile.o tileCalc.o tileStructEdit.o tileFileIO.o tileUtils.o tileMisc.o tile.h
	gcc -o tile tile.o tileCalc.o tileStructEdit.o tileFileIO.o tileUtils.o tileMisc.o

# Random Utils
tipsyPrintRho: tipsyPrintRho.o tileCalc.o tileStructEdit.o tileFileIO.o tileUtils.o tileMisc.o tile.h
	gcc -o tipsyPrintRho tipsyPrintRho.o tileCalc.o tileStructEdit.o tileFileIO.o tileUtils.o tileMisc.o

tipsyPrintRho.o: tipsyPrintRho.c tile.h
	gcc -c ./tipsyPrintRho.c

# Functions
tile.o: tile.c tile.h
	gcc -c tile.c

tileCalc.o: tileCalc.c tile.h
	gcc -c tileCalc.c

tileStructEdit.o: tileStructEdit.c tile.h
	gcc -c tileStructEdit.c

tileFileIO.o: tileFileIO.c tile.h
	gcc -c tileFileIO.c

tileUtils.o: tileUtils.c tile.h
	gcc -c tileUtils.c

tileMisc.o: tileMisc.c tile.h
	gcc -c tileMisc.c
