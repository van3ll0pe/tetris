#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../include/screen.h"
#include "../include/macros.h"
#include "../include/map.h"

void key_pressed_callFunction(Map *map);



void check_looseGame(Screen *screen, Map *map) {
    if (map->m_loose == 1) {
        printf("loose\n");
        screen->m_isRunning = 0;
    }
}

int main(int ac, char **av) {

    int timer; //the clock to automove down
    int timePassed = 0; //the time passed to check the timer


    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return EXIT_FAILURE;
    }

    if (TTF_Init() == -1) {
        return EXIT_FAILURE;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        return EXIT_FAILURE;
    }

    //+ 200 to put the next tetrimino and text
    Screen screen = screen_init((BLOCK_WIDTH * MAP_WIDTH) + 200, (BLOCK_HEIGHT * MAP_HEIGHT), "TETRIS LIKE");
    if (screen.init_sdl(&screen) == 1) {
        return EXIT_FAILURE;
    }

    Map map = map_init(&screen);
    
    Mix_Music *musicGame = NULL;
    musicGame = Mix_LoadMUS("data/music/tetris-music.mp3");

    if (musicGame == NULL) {
        return EXIT_FAILURE;
    }

    Mix_PlayMusic(musicGame, -1);
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
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

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