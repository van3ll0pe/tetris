#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "macros.h"
#include "screen.h"
#include "tetrimino.h"
#include "scoringzone.h"

typedef struct Map Map;


//------PROTOTYPES------------------

Map map_init(Screen *screen);         //function to init map
void map_display_map(Screen *screen, Map *map); //function to display the map
void map_display_tetrimino(Screen *screen, Map *map); //function to display the tetrimino
void map_move_tetrimino(Map *map, int sideMove); //function to move on right or left
void map_rotation_tetrimino(Map *map, int sideRotation); //function to rotate tretrimino
void map_automove_down(Map *map); //function to move automaticly down
void map_cleanLine(Map *map); //function to clean line if the line is full
void map_increaseSpeed(Map *map); //function to increase speed while the lines breaked


void map_piece_toRotationPiece(Map *map); //function to set the piece into rotation piece
void map_rotationPiece_toPiece(Map *map); //function to set the rotation piece into piece

//----------------------------------


struct Map {

    int **m_mapVerification; //the tab of tab check each line

    Tetrimino tetrimino; //the actual piece to put on the map (it is changed by m_nbrValueTetrimino)
    Tetrimino tetriminoNext; //the next piece to put on the map (it is changed by m_nbrValueTetrimino)
    ScoringZone scoringZone; //the scoring zone of the map
    
    int m_loose; //if 0 the player doesn't loose the game, if 1 the game stop
    int m_nbrLineBreak; //the number of lines destroyed
    int m_speed;        //the speed of tetriminos in while points
    int m_nbrValueTetrimino;    //the random value to set piece tetrimino
    int m_nbrValueTetriminoNext; //the next random value tetrimino





    void (*display_map)(Screen *screen, Map *map); //pointer of function map_display_map
    void (*display_tetrimino)(Screen *screen, Map *map); //pointer of function map_display_tetrimino
    void (*move_tetrimino)(Map *map, int sideMove); //pointer of function map_move_tetrimino
    void (*automove_down)(Map *map); //pointer of function map_automove_down
    void (*rotation_tetrimino)(Map *map, int sideRotation); //pointer of function map_rotation_tetrimino
    void (*cleanLine)(Map *map); //pointer of function map_cleanLine
    void (*increaseSpeed)(Map *map); //pointer of function map_increaseSpeed
};


#endif