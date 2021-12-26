#include "../include/tetrimino.h"


Tetrimino tetrimino_init(int nbrValue) {
    Tetrimino tetrimino;

    tetrimino.m_position_x = 3;
    tetrimino.m_position_y = 0;

    switch (nbrValue) {
    case 0: //I tetrimino
            tetrimino.m_sizeSquare = 4;
            //create a small square of 4 * 4 for the I piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 4; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 4; x++) { //put all 0 in the square
                    tetrimino.m_piece[y][x] = 0;
                    tetrimino.m_pieceRotation[y][x] = 0;
                }
            }
            //set the position of the piece in the small square
            tetrimino.m_piece[1][0] = 1; 
            tetrimino.m_piece[1][1] = 1;
            tetrimino.m_piece[1][2] = 1;
            tetrimino.m_piece[1][3] = 1;

            tetrimino.m_pieceRotation[1][0] = 1; 
            tetrimino.m_pieceRotation[1][1] = 1;
            tetrimino.m_pieceRotation[1][2] = 1;
            tetrimino.m_pieceRotation[1][3] = 1;

            break;

    case 1: //O tetrimino
            tetrimino.m_sizeSquare = 2;
            //create a small square of 2 * 2 for the O piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set the lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 2; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 2; x++) {
                    tetrimino.m_piece[y][x] = 0; //put all 0 in the square
                    tetrimino.m_pieceRotation[y][x] = 0; //put all 0 in the square
                }
            }
            //set the position of the piece in the small square
            tetrimino.m_piece[0][0] = 2;
            tetrimino.m_piece[0][1] = 2;
            tetrimino.m_piece[1][0] = 2;
            tetrimino.m_piece[1][1] = 2;

            tetrimino.m_pieceRotation[0][0] = 2;
            tetrimino.m_pieceRotation[0][1] = 2;
            tetrimino.m_pieceRotation[1][0] = 2;
            tetrimino.m_pieceRotation[1][1] = 2;

            break;

    case 2: //T tetrimino
            tetrimino.m_sizeSquare = 3;
            //create a small square of 3 *3 for the T piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set the lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 3; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 3; x++) {
                    tetrimino.m_piece[y][x] = 0;  //put all 0 in the square
                    tetrimino.m_pieceRotation[y][x] = 0;
                }
            }

            tetrimino.m_piece[1][0] = 3;
            tetrimino.m_piece[1][1] = 3;
            tetrimino.m_piece[1][2] = 3;
            tetrimino.m_piece[2][1] = 3;

            tetrimino.m_pieceRotation[1][0] = 3;
            tetrimino.m_pieceRotation[1][1] = 3;
            tetrimino.m_pieceRotation[1][2] = 3;
            tetrimino.m_pieceRotation[2][1] = 3;

            break;

    case 3: //S tetrimino
            tetrimino.m_sizeSquare = 3;
            //create a small square of 3 *3 for the S piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set the lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 3; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 3; x++) {
                    tetrimino.m_piece[y][x] = 0;  //put all 0 in the square
                    tetrimino.m_pieceRotation[y][x] = 0;  //put all 0 in the square
                }
            }

            tetrimino.m_piece[1][0] = 4;
            tetrimino.m_piece[1][1] = 4;
            tetrimino.m_piece[0][1] = 4;
            tetrimino.m_piece[0][2] = 4;

            tetrimino.m_pieceRotation[1][0] = 4;
            tetrimino.m_pieceRotation[1][1] = 4;
            tetrimino.m_pieceRotation[0][1] = 4;
            tetrimino.m_pieceRotation[0][2] = 4;
            break;

    case 4: //Z tetrimino
            tetrimino.m_sizeSquare = 3;
            //create a small square of 3 *3 for the Z piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set the lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 3; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 3; x++) {
                    tetrimino.m_piece[y][x] = 0;  //put all 0 in the square
                    tetrimino.m_pieceRotation[y][x] = 0;  //put all 0 in the square
                }
            }

            tetrimino.m_piece[0][0] = 5;
            tetrimino.m_piece[0][1] = 5;
            tetrimino.m_piece[1][1] = 5;
            tetrimino.m_piece[1][2] = 5;

            tetrimino.m_pieceRotation[0][0] = 5;
            tetrimino.m_pieceRotation[0][1] = 5;
            tetrimino.m_pieceRotation[1][1] = 5;
            tetrimino.m_pieceRotation[1][2] = 5;

            break;

    case 5: //L tetrimino
            tetrimino.m_sizeSquare = 3;
            //create a small square of 3 *3 for the L piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set the lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 3; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 3; x++) {
                    tetrimino.m_piece[y][x] = 0;  //put all 0 in the square
                    tetrimino.m_pieceRotation[y][x] = 0;  //put all 0 in the square
                }
            }
            
            tetrimino.m_piece[0][1] = 6;
            tetrimino.m_piece[1][1] = 6;
            tetrimino.m_piece[2][1] = 6;
            tetrimino.m_piece[2][2] = 6;

            tetrimino.m_pieceRotation[0][1] = 6;
            tetrimino.m_pieceRotation[1][1] = 6;
            tetrimino.m_pieceRotation[2][1] = 6;
            tetrimino.m_pieceRotation[2][2] = 6;

            break;

    case 6: //J tetrimino
            tetrimino.m_sizeSquare = 3;
            //create a small square of 3 *3 for the J piece
            tetrimino.m_piece = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set the lines
            tetrimino.m_pieceRotation = (int **)malloc(sizeof(int *) * tetrimino.m_sizeSquare); //set lines
            for (int y = 0; y < 3; y++) { //set columns
                tetrimino.m_piece[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                tetrimino.m_pieceRotation[y] = (int *)malloc(sizeof(int) * tetrimino.m_sizeSquare);
                for (int x = 0; x < 3; x++) {
                    tetrimino.m_piece[y][x] = 0;  //put all 0 in the square
                    tetrimino.m_pieceRotation[y][x] = 0;  //put all 0 in the square
                }
            }

            tetrimino.m_piece[0][1] = 7;
            tetrimino.m_piece[1][1] = 7;
            tetrimino.m_piece[2][1] = 7;
            tetrimino.m_piece[2][0] = 7;

            tetrimino.m_pieceRotation[0][1] = 7;
            tetrimino.m_pieceRotation[1][1] = 7;
            tetrimino.m_pieceRotation[2][1] = 7;
            tetrimino.m_pieceRotation[2][0] = 7;

            break;
    
    default: break;
    }  

    return tetrimino;
}