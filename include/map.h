#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "macros.h"
#include "screen.h"
#include "tetrimino.h"

typedef struct Map Map;


//------PROTOTYPES------------------

Map map_init();         //function to init map
void map_display_map(Screen *screen, Map *map); //function to display the map
void map_display_tetrimino(Screen *screen, Map *map); //function to display the tetrimino
void map_move_tetrimino(Map *map); //function to move on right or left
void map_rotation_tetrimino(Map *map); //function to rotate tretrimino
void map_automove_down(Map *map); //function to move automaticly down
void map_cleanLine(Map *map); //function to clean line if the line is full


void map_piece_toRotationPiece(Map *map); //function to set the piece into rotation piece
void map_rotationPiece_toPiece(Map *map); //function to set the rotation piece into piece

//----------------------------------


struct Map {

    int **m_mapVerification; //the tab of tab check each line

    Tetrimino tetrimino; //the actual piece to put on the map (it is changed by m_nbrValueTetrimino)
    int m_stateTetrimino; //the value if we need a new tetrimino or not. 0 -> keep the piece | 1 -> have a new tetrimino

    int m_nbrLineBreak; //the number of lines destroyed
    int m_points;       //the points given to destroy line
    int m_speed;        //the speed of tetriminos in while points
    int m_nbrValueTetrimino;    //the random value to set piece tetrimino

    void (*display_map)(Screen *screen, Map *map); //pointer of function map_display_map
    void (*display_tetrimino)(Screen *screen, Map *map); //pointer of function map_display_tetrimino
    void (*move_tetrimino)(Map *map); //pointer of function map_move_tetrimino
    void (*automove_down)(Map *map); //pointer of function map_automove_down
    void (*rotation_tetrimino)(Map *map); //pointer of function map_rotation_tetrimino
    void (*cleanLine)(Map *map);
};


#endif