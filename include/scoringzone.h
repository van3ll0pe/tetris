#ifndef SCORINGZONE_H
#define SCORINGZONE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.h"
#include "macros.h"


typedef struct ScoringZone ScoringZone;
typedef struct Map Map;

//-------- PROTOTYPES FUNCTIONS ----------------------------
ScoringZone scoringZone_init(Screen *screen); //the function to init the scoring_zone
void scoringZone_display(Screen *screen, ScoringZone *scoringZone, Map *map); //function to display the Scoring ZONE
//----------------------------------------------------------


struct ScoringZone {
    SDL_Rect separationBarre; //la barre qui sépare la map de jeu et la scoring zone

    SDL_Rect squareBordure; //le plus grand carré (en blanc qui servira de bordure pour afficher la piece suivante)
    SDL_Rect squareInside; //le petit carré (en noir à l'intérieur du grand carré blanc afin de faire une bordure carré épaisse)

    TTF_Font * font; //the font of the text

    char *nextPiece_sentence; //the sentence to display "NEXT :"

    SDL_Color text_color; //the color of the text

    SDL_Surface *text_surface; //to put the text on a surface
    SDL_Texture *text_texture; //to copy the surface on the texture to display on the renderer after

    void (*display)(Screen *screen, ScoringZone *scoringZone, Map *map); //pointer of function scoringZone_display;

};


#endif