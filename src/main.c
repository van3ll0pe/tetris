#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "../include/screen.h"
#include "../include/macros.h"
#include "../include/map.h"



int main(int ac, char **av) {

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

        map.move_tetrimino(&map); //move tetrimino left- right
        map.rotation_tetrimino(&map);
        map.automove_down(&map); //down to tetrimino
        map.cleanLine(&map);

        SDL_RenderPresent(screen.m_render);
        SDL_Delay(150);
    }

    screen.destroy(&screen);
    SDL_Quit();

    return EXIT_SUCCESS;
}