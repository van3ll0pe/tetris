#include "../include/map.h"

ScoringZone scoringZone_init(Screen *screen) {
    ScoringZone scoringZone;

    scoringZone.font = NULL;
    scoringZone.font = TTF_OpenFont("data/font/ARCADECLASSIC.TTF", 16);
    if (scoringZone.font == NULL) {
        fprintf(stderr, "probleme de font\n");
    }

    scoringZone.separationBarre.y = 0;
    scoringZone.separationBarre.x = MAP_WIDTH * BLOCK_WIDTH;
    scoringZone.separationBarre.h = MAP_HEIGHT * BLOCK_HEIGHT;
    scoringZone.separationBarre.w = 10;


    scoringZone.nextPiece_sentence = "NEXT";

    scoringZone.squareBordure.x = 350;
    scoringZone.squareBordure.y = 50;
    scoringZone.squareBordure.h = 100;
    scoringZone.squareBordure.w = 100;

    scoringZone.squareInside.x = 360;
    scoringZone.squareInside.y = 60;
    scoringZone.squareInside.h = 80;
    scoringZone.squareInside.w = 80;

    scoringZone.text_color.a = 255;
    scoringZone.text_color.b = 255;
    scoringZone.text_color.g = 255;
    scoringZone.text_color.r = 255;

    //get the text in a surface and put in texture
    scoringZone.text_surface = TTF_RenderText_Solid(scoringZone.font, scoringZone.nextPiece_sentence, scoringZone.text_color);
    scoringZone.text_texture = SDL_CreateTextureFromSurface(screen->m_render, scoringZone.text_surface);

    SDL_FreeSurface(scoringZone.text_surface);

    scoringZone.display = &scoringZone_display;

    return (scoringZone);
}

void scoringZone_display(Screen *screen, ScoringZone *scoringZone, Map *map) {

    SDL_Rect position_nextPiece_sentence;
    SDL_Rect position_nextTetrimino;

    //set the position of the "NEXT" sentence
    position_nextPiece_sentence.x = 350;
    position_nextPiece_sentence.y = 30;
    position_nextPiece_sentence.w = 100;
    position_nextPiece_sentence.h = 16;

    //Draw the White square and the separate barre
    SDL_SetRenderDrawColor(screen->m_render, 255, 255, 255, 255);
    SDL_RenderFillRect(screen->m_render, &scoringZone->separationBarre);
    SDL_RenderFillRect(screen->m_render, &scoringZone->squareBordure);

    //draw the black square in the white square
    SDL_SetRenderDrawColor(screen->m_render, 0, 0, 0, 255);
    SDL_RenderFillRect(screen->m_render, &scoringZone->squareInside);


    //and copy the texture in the render
    SDL_RenderCopy(screen->m_render, scoringZone->text_texture, NULL, &position_nextPiece_sentence);

    //set the tetrimino in the block
    position_nextTetrimino.h = 20;
    position_nextTetrimino.w = 20;

    for (int y = 0; y < map->tetriminoNext.m_sizeSquare; y++) {
        for (int x = 0; x <map->tetriminoNext.m_sizeSquare; x++) {

            position_nextTetrimino.x = ((x+1) * 20 - 20) + 360;
            position_nextTetrimino.y = ((y+1) * 20 - 20) + 60;

            if (map->tetriminoNext.m_piece[y][x] > 0) {
                switch (map->tetriminoNext.m_piece[y][x]) {
                    case 1: //I tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, CYAN_R, CYAN_G, CYAN_B, 255);
                            break;
                    case 2: //O tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, YELLOW_R, YELLOW_G, YELLOW_B, 255);
                            break;
                    case 3: //T tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, PURPLE_R, PURPLE_G, PURPLE_B, 255);
                            break;
                    case 4: //S tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, GREEN_R, GREEN_G, GREEN_B, 255);
                            break;
                    case 5: //Z tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, RED_R, RED_G, RED_B, 255);
                            break;
                    case 6: //L tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, ORANGE_R, ORANGE_G, ORANGE_B, 255);
                            break;
                    case 7: //J tetrimino
                            SDL_SetRenderDrawColor(screen->m_render, BLUE_R, BLUE_G, BLUE_B, 255);
                            break;
                    default :
                            break;

                }
                SDL_RenderFillRect(screen->m_render, &position_nextTetrimino);
            }
        }
    }


}