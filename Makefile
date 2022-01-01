CC 	= gcc
LIBS 	= -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
CHECKS	= -Wall -g
INC	= -I ./include
OUT	= -o tetris
SRC	= src/main.c	\
	  src/map.c	\
	  src/scoringzone.c	\
	  src/screen.c	\
	  src/tetrimino.c

OBJ	= *.o

compile :	
	$(CC) -c $(SRC)

link	:
	$(CC) $(OBJ) $(LIBS) $(CHECKS) $(INC) $(OUT)

clear	:	
	rm -rf *.o
