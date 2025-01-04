all:
	gcc -Isrc/Include -Lsrc/Lib -o main main.c -lmingw32 -lSDL2main -lSDL2