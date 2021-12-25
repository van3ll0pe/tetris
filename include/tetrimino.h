#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <time.h>

typedef struct Tetrimino Tetrimino;

//-----PROTOTYPES-----------------------
Tetrimino tetrimino_init(int nbrValue); //the function to init tetrimino
//--------------------------------------

struct Tetrimino {
    int **m_piece; //the piece on the tab
    int **m_pieceRotation;  //the piece to check rotation before apply on m_piece
    int m_sizeSquare; //the size of small square for each tetrimino
    int m_position_x; //the position x of the piece
    int m_position_y;  //the position y of the piece
};

#endif