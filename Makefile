tile: tile.o tileFileIO.o tileMisc.o tile.h
	gcc -o tile tile.o tileFileIO.o tileMisc.o

tile.o: tile.c tile.h
	gcc -c tile.c

tileFileIO.o: tileFileIO.c tile.h
	gcc -c tileFileIO.c

tileMisc.o: tileMisc.c tile.h
	gcc -c tileMisc.c
