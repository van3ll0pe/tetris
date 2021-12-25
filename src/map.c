#include "../include/map.h"

Map map_init() {

    Map map;

    map.m_points = 0;
    map.m_speed = 200;
    map.m_stateTetrimino = 0;

    //malloc the tabVerification & map REct
    map.m_mapVerification = (int **)malloc(sizeof(int *) * MAP_HEIGHT);

    for (int i = 0; i < MAP_HEIGHT; i++) {
        map.m_mapVerification[i] = (int*)malloc(sizeof(int) * MAP_WIDTH);
    }
    //init the tab of tab. Verification & map color
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map.m_mapVerification[y][x] = 0;
        }
    }

    //give the piece tetrimino
    srand( time(NULL));
    map.m_nbrValueTetrimino = rand() % 7;
    

    //create the piece tetrimino
    map.tetrimino = tetrimino_init(map.m_nbrValueTetrimino);

    map.display_map = &map_display_map;
    map.display_tetrimino = &map_display_tetrimino;
    map.move_tetrimino = &map_move_tetrimino;
    map.automove_down = &map_automove_down;
    map.rotation_tetrimino = &map_rotation_tetrimino;

    return map;
}


void map_display_map(Screen *screen, Map *map) {
    
    SDL_Rect block; //each block of the map to display
    block.h = BLOCK_HEIGHT;
    block.w = BLOCK_WIDTH;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {

            //set the position to display the block in while position in the tab
            block.x = (((x+1) * BLOCK_WIDTH) - BLOCK_WIDTH);
            block.y = (((y+1) * BLOCK_HEIGHT) - BLOCK_HEIGHT);
            switch (map->m_mapVerification[y][x]) {
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
                default : //if 0
                        SDL_SetRenderDrawColor(screen->m_render, 0, 0, 0, 255);
                        break;

            }
            SDL_RenderFillRect(screen->m_render, &block);
        }
    }
}


void map_display_tetrimino(Screen *screen, Map *map) {
    
    SDL_Rect block;
    block.h = BLOCK_HEIGHT;
    block.w = BLOCK_WIDTH;

    for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
        for (int x = 0; x < map->tetrimino.m_sizeSquare; x++) {
            
            block.x = (map->tetrimino.m_position_x + x+1) * BLOCK_WIDTH - BLOCK_WIDTH;
            block.y = (map->tetrimino.m_position_y + y+1) * BLOCK_HEIGHT - BLOCK_HEIGHT;

            if (map->tetrimino.m_piece[y][x] > 0) {
                switch (map->tetrimino.m_piece[y][x]) {
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
                SDL_RenderFillRect(screen->m_render, &block);
            }
        }
    }
}


void map_move_tetrimino(Map *map) {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL); //the state of keyboard
    int borderLeft[map->tetrimino.m_sizeSquare]; //la délimitation de la piece à gauche
    int borderRight[map->tetrimino.m_sizeSquare]; //la délimitation de la pièce à droite
    int valideNextPosition = 0; 


    //Set border right side

    for (int y = 0, i = 0; y < map->tetrimino.m_sizeSquare; y++, i++) { //je parcours chaque colonne, si il y a n zero alors la bordure est décalé
        int x = map->tetrimino.m_sizeSquare - 1;
        borderRight[i] = 0;
        while (x >= 0 && map->tetrimino.m_piece[y][x] == 0) {
            borderRight[i]++;
            x--;
        }
    }

    //set border left side
    for (int y = 0, i = 0; y < map->tetrimino.m_sizeSquare; y++, i++) { //je parcours chaque colonne, si il y a n zero alors la bordure est décalé
        int x = 0;
        borderLeft[i] = 0;
        while (x < map->tetrimino.m_sizeSquare && map->tetrimino.m_piece[y][x] == 0) {
            borderLeft[i]++;
            x++;
        }
    }
    
    for (int i = 0; i < map->tetrimino.m_sizeSquare; i++) {
        printf("%d : bordure gauche %d - bordure droite %d\n", i, borderLeft[i], borderRight[i]);
    }


    //déplacement en fonction de la bordure

    if (keyboard[SDL_SCANCODE_LEFT]) {
        for (int y = map->tetrimino.m_position_y, i = 0; y < map->tetrimino.m_position_y + map->tetrimino.m_sizeSquare; y++, i++) {
            if (borderLeft[i] == map->tetrimino.m_sizeSquare) {
                valideNextPosition++;
            }
            else if ((map->tetrimino.m_position_x + borderLeft[i]) > 0 && map->m_mapVerification[y][map->tetrimino.m_position_x + borderLeft[i] - 1] == 0) {
                valideNextPosition++;
            }
        }

        if (valideNextPosition == map->tetrimino.m_sizeSquare) {
            map->tetrimino.m_position_x--;
        }
        /*
        if ((map->tetrimino.m_position_x + borderLeft) > 0) {
                map->tetrimino.m_position_x--;
        }*/

    } else if (keyboard[SDL_SCANCODE_RIGHT]) {
        
        for (int y = map->tetrimino.m_position_y, i = 0; y < map->tetrimino.m_position_y + map->tetrimino.m_sizeSquare; y++, i++) {
            if (borderRight[i] == map->tetrimino.m_sizeSquare) {
                valideNextPosition++;
            }
            else if ((map->tetrimino.m_position_x + map->tetrimino.m_sizeSquare - borderRight[i] < MAP_WIDTH) && (map->m_mapVerification[y][map->tetrimino.m_position_x + map->tetrimino.m_sizeSquare - borderRight[i]] == 0)) {
                valideNextPosition++;
            }
        }

        if (valideNextPosition == map->tetrimino.m_sizeSquare) {
            map->tetrimino.m_position_x++;
        }
        /*
        if ((map->tetrimino.m_position_x + (map->tetrimino.m_sizeSquare - borderRight)) < MAP_WIDTH) {
            map->tetrimino.m_position_x++;
        }*/
    }

       
}

void map_automove_down(Map *map) {
    int endLinePiece[map->tetrimino.m_sizeSquare];
    int valideNextPosition = 0;

    //check the border of each columns of piece from the bottom
    for (int x = 0; x < map->tetrimino.m_sizeSquare; x++) {
        endLinePiece[x] = 0;
        int y = map->tetrimino.m_sizeSquare - 1;
        while (y >= 0 && map->tetrimino.m_piece[y][x] == 0) {
            endLinePiece[x] += 1;
            y--;
        }
    }
    //on parcours le petit carré du tetrimino dans la grande map si une ligne du petit carré est vide alors c'est valide, sinon si il y a un 0 sous la ligne alors c'est valide
    for (int x = map->tetrimino.m_position_x, i = 0; x < (map->tetrimino.m_position_x + map->tetrimino.m_sizeSquare); x++, i++) {
        if (endLinePiece[i] == map->tetrimino.m_sizeSquare) {
            valideNextPosition++;
        }
        else if ((map->tetrimino.m_position_y + map->tetrimino.m_sizeSquare - endLinePiece[i] < MAP_HEIGHT) && (map->m_mapVerification[map->tetrimino.m_position_y + map->tetrimino.m_sizeSquare - endLinePiece[i]][x] == 0)) {
            valideNextPosition++;
        }
    //valide 
    }
    //si la piece est valide pour le même nombre de largeur du tetrimino alors la pièce peut descendre, sinon la pièce ne peut plus bouger alors on l'ajoute dans la grande map et on créer un nouveau tetrimino
    if (valideNextPosition == map->tetrimino.m_sizeSquare) {
        map->tetrimino.m_position_y++;
    } else {
        //on calque la piece dans la map
        for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
            for (int x = 0; x < map->tetrimino.m_sizeSquare; x++) {
                if (map->tetrimino.m_piece[y][x] > 0) {
                    map->m_mapVerification[map->tetrimino.m_position_y + y][map->tetrimino.m_position_x + x] = map->tetrimino.m_piece[y][x];
                }
            }
        }

        srand(time(NULL));
        map->m_nbrValueTetrimino = rand() % 7;
        map->tetrimino = tetrimino_init(map->m_nbrValueTetrimino);
    }




}

void map_rotation_tetrimino(Map *map) {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);



    int transfertValue = 0; //the tmp variable to transfert
    int borderLeftRotation = 0;
    int borderRightRotation = 0;


    if (keyboard[SDL_SCANCODE_Q]) {
        if (map->m_nbrValueTetrimino == 0) { //si le tetrimino est un I
            //corner block
            transfertValue = map->tetrimino.m_pieceRotation[3][0];
            map->tetrimino.m_pieceRotation[3][0] = map->tetrimino.m_pieceRotation[0][0];
            map->tetrimino.m_pieceRotation[0][0] = map->tetrimino.m_pieceRotation[0][3];
            map->tetrimino.m_pieceRotation[0][3] = map->tetrimino.m_pieceRotation[3][3];
            map->tetrimino.m_pieceRotation[3][3] = transfertValue;

            //part 1 side block
            transfertValue = map->tetrimino.m_pieceRotation[3][2];
            map->tetrimino.m_pieceRotation[3][2] = map->tetrimino.m_pieceRotation[2][0];
            map->tetrimino.m_pieceRotation[2][0] = map->tetrimino.m_pieceRotation[0][1];
            map->tetrimino.m_pieceRotation[0][1] = map->tetrimino.m_pieceRotation[1][3];
            map->tetrimino.m_pieceRotation[1][3] = transfertValue;

            //part 2 side block
            transfertValue = map->tetrimino.m_pieceRotation[3][1];
            map->tetrimino.m_pieceRotation[3][1] = map->tetrimino.m_pieceRotation[1][0];
            map->tetrimino.m_pieceRotation[1][0] = map->tetrimino.m_pieceRotation[0][2];
            map->tetrimino.m_pieceRotation[0][2] = map->tetrimino.m_pieceRotation[2][3];
            map->tetrimino.m_pieceRotation[2][3] = transfertValue;

            //center block

            transfertValue = map->tetrimino.m_pieceRotation[2][2];
            map->tetrimino.m_pieceRotation[2][2] = map->tetrimino.m_pieceRotation[2][1];
            map->tetrimino.m_pieceRotation[2][1] = map->tetrimino.m_pieceRotation[1][1];
            map->tetrimino.m_pieceRotation[1][1] = map->tetrimino.m_pieceRotation[1][2];
            map->tetrimino.m_pieceRotation[1][2] = transfertValue;


        } else if (map->m_nbrValueTetrimino >= 2 && map->m_nbrValueTetrimino <= 6) { //si il n'est pas un I ou un O
            //corner block of piece
            transfertValue = map->tetrimino.m_pieceRotation[0][0];
            map->tetrimino.m_pieceRotation[0][0] = map->tetrimino.m_pieceRotation[0][2];
            map->tetrimino.m_pieceRotation[0][2] = map->tetrimino.m_pieceRotation[2][2];
            map->tetrimino.m_pieceRotation[2][2] = map->tetrimino.m_pieceRotation[2][0];
            map->tetrimino.m_pieceRotation[2][0] = transfertValue;

            //center block
            transfertValue = map->tetrimino.m_pieceRotation[0][1];
            map->tetrimino.m_pieceRotation[0][1] = map->tetrimino.m_pieceRotation[1][2];
            map->tetrimino.m_pieceRotation[1][2] = map->tetrimino.m_pieceRotation[2][1];
            map->tetrimino.m_pieceRotation[2][1] = map->tetrimino.m_pieceRotation[1][0];
            map->tetrimino.m_pieceRotation[1][0] = transfertValue;
        }

        
        
    } else if (keyboard[SDL_SCANCODE_D]) {

        if (map->m_nbrValueTetrimino == 0) { //si le tetrimino est un I
            //corner block
            transfertValue = map->tetrimino.m_pieceRotation[3][0];
            map->tetrimino.m_pieceRotation[3][0] = map->tetrimino.m_pieceRotation[0][0];
            map->tetrimino.m_pieceRotation[0][0] = map->tetrimino.m_pieceRotation[0][3];
            map->tetrimino.m_pieceRotation[0][3] = map->tetrimino.m_pieceRotation[3][3];
            map->tetrimino.m_pieceRotation[3][3] = transfertValue;

            //part 1 side block
            transfertValue = map->tetrimino.m_pieceRotation[3][2];
            map->tetrimino.m_pieceRotation[3][2] = map->tetrimino.m_pieceRotation[2][0];
            map->tetrimino.m_pieceRotation[2][0] = map->tetrimino.m_pieceRotation[0][1];
            map->tetrimino.m_pieceRotation[0][1] = map->tetrimino.m_pieceRotation[1][3];
            map->tetrimino.m_pieceRotation[1][3] = transfertValue;

            //part 2 side block
            transfertValue = map->tetrimino.m_pieceRotation[3][1];
            map->tetrimino.m_pieceRotation[3][1] = map->tetrimino.m_pieceRotation[1][0];
            map->tetrimino.m_pieceRotation[1][0] = map->tetrimino.m_pieceRotation[0][2];
            map->tetrimino.m_pieceRotation[0][2] = map->tetrimino.m_pieceRotation[2][3];
            map->tetrimino.m_pieceRotation[2][3] = transfertValue;

            //center block

            transfertValue = map->tetrimino.m_pieceRotation[2][2];
            map->tetrimino.m_pieceRotation[2][2] = map->tetrimino.m_pieceRotation[2][1];
            map->tetrimino.m_pieceRotation[2][1] = map->tetrimino.m_pieceRotation[1][1];
            map->tetrimino.m_pieceRotation[1][1] = map->tetrimino.m_pieceRotation[0][2];
            map->tetrimino.m_pieceRotation[1][2] = transfertValue;

        } else if (map->m_nbrValueTetrimino >= 2 && map->m_nbrValueTetrimino <= 6) { //si il n'est pas un I ou un O
            //corner block of tetrimino
            transfertValue =  map->tetrimino.m_pieceRotation[0][2];
            map->tetrimino.m_pieceRotation[0][2] = map->tetrimino.m_pieceRotation[0][0];
            map->tetrimino.m_pieceRotation[0][0] = map->tetrimino.m_pieceRotation[2][0];
            map->tetrimino.m_pieceRotation[2][0] = map->tetrimino.m_pieceRotation[2][2];
            map->tetrimino.m_pieceRotation[2][2] = transfertValue;

            //center block
            transfertValue = map->tetrimino.m_pieceRotation[0][1];
            map->tetrimino.m_pieceRotation[0][1] = map->tetrimino.m_pieceRotation[1][0];
            map->tetrimino.m_pieceRotation[1][0] = map->tetrimino.m_pieceRotation[2][1];
            map->tetrimino.m_pieceRotation[2][1] = map->tetrimino.m_pieceRotation[1][2];
            map->tetrimino.m_pieceRotation[1][2] = transfertValue;

        }


    }


    for (int x = map->tetrimino.m_sizeSquare-1; x >= map->tetrimino.m_sizeSquare - 2; x--) { //je parcours chaque colonne, si il y a n zero alors la bordure est décalé
       int valideBorder = 0;
        for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
            if (map->tetrimino.m_pieceRotation[y][x] == 0) {
                valideBorder++;
            }
        }
        if (valideBorder == map->tetrimino.m_sizeSquare) {
            borderRightRotation++;
        }
    }

    for (int x = 0; x <= map->tetrimino.m_sizeSquare - 2; x++) {
        int valideBorder = 0;
        for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
            if (map->tetrimino.m_pieceRotation[y][x] == 0) {
                valideBorder++;
            }
        }
        if (valideBorder == map->tetrimino.m_sizeSquare) {
            borderLeftRotation++;
        }
    }

    //check collision with opthers tetrimino
    for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
        for (int x = 0; x < map->tetrimino.m_sizeSquare; x++) {
            //check to map with the rotation piece to see if there are collision
        }
    }

    if () {

    }
    if (((map->tetrimino.m_position_x + borderLeftRotation) >= 0) && ((map->tetrimino.m_position_x + (map->tetrimino.m_sizeSquare - borderRightRotation)) <= MAP_WIDTH)) {
        map_piece_toRotationPiece(map);
    }else {
        map_rotationPiece_toPiece(map);
    }
}

/**
 * @brief Function to set the piece to the new piece with rotation
 * 
 * @param map 
 */
void map_piece_toRotationPiece(Map *map) {
   for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
       for (int x = 0; x < map->tetrimino.m_sizeSquare; x++) {
           map->tetrimino.m_piece[y][x] = map->tetrimino.m_pieceRotation[y][x];
       }
   }
}


/**
 * @brief Function to set the rotation piece like the piece 
 * 
 * @param map 
 */
void map_rotationPiece_toPiece(Map *map) {
    for (int y = 0; y < map->tetrimino.m_sizeSquare; y++) {
       for (int x = 0; x < map->tetrimino.m_sizeSquare; x++) {
           map->tetrimino.m_pieceRotation[y][x] = map->tetrimino.m_piece[y][x];
       }
   }
}