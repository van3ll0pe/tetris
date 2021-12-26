#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "../include/screen.h"
#include "../include/macros.h"
#include "../include/map.h"

void key_pressed_callFunction(Map *map);

void key_pressed_callFunction(Map *map) {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    if (keyboard[SDL_SCANCODE_Q]) { //rotation à gauche
        map->rotation_tetrimino(map, 1);
    }
    else if (keyboard[SDL_SCANCODE_D]) {//rotation à droite
        map->rotation_tetrimino(map, 2);    
    }
    else if (keyboard[SDL_SCANCODE_LEFT]) { //deplacement vers la gauche
        map->move_tetrimino(map, 1);
    }
    else if (keyboard[SDL_SCANCODE_RIGHT]) { //deplacement vers la droite
        map->move_tetrimino(map, 2);
    } else if (keyboard[SDL_SCANCODE_DOWN]) {
        map->m_speed = 0;
    } else if (keyboard[SDL_SCANCODE_DOWN] == 0) {
        map->m_speed = 900;
    }
}

void check_looseGame(Screen *screen, Map *map) {
    if (map->m_loose == 1) {
        printf("loose\n");
        screen->m_isRunning = 0;
    }
}

int main(int ac, char **av) {
    int timer; //the clock to automove down
    int timePassed = 0; //the time passed to check the timer

    Screen screen = screen_init(BLOCK_WIDTH * 10, BLOCK_HEIGHT * 20, "TETRIS LIKE");
    Map map = map_init();

    if (screen.init_sdl(&screen) == 1) {
        return EXIT_FAILURE;
    }

    while (screen.m_isRunning) {

        screen.adaptRender(&screen);
        screen.getEvent(&screen);

        screen.clear(&screen);

        

        map.display_map(&screen, &map); //display block on the map
        map.display_tetrimino(&screen, &map); //display the actual tetrimino

        key_pressed_callFunction(&map);

        timer = SDL_GetTicks();
        if (timer > timePassed + map.m_speed) {
            map.automove_down(&map); //down to tetrimino
            map.increaseSpeed(&map);
            timePassed = timer;
        }

        map.cleanLine(&map);     //check to clear line
        
        SDL_RenderPresent(screen.m_render);
        SDL_Delay(150);
        check_looseGame(&screen, &map); //à revoir /!
    }

    printf("lines : %d\n", map.m_nbrLineBreak);
    screen.destroy(&screen);
    SDL_Quit();

    return EXIT_SUCCESS;
}