#include "../include/screen.h"


/**
 * FUNCTION TO INIT THE STRUCTURE SCREEN 
 * 
 *  RETURN A SCREEN 
 */
Screen screen_init(int w, int h, char *title) {
    Screen screen;

    screen.m_isRunning     = 1;
    screen.m_widthWindow   = w;
    screen.m_heightWindow  = h;
    screen.m_ratioScreenBegin   = screen.m_widthWindow / screen.m_heightWindow;
    screen.m_titleWindow   = title;
    screen.m_window        = NULL;
    screen.m_render        = NULL;


    screen.init_sdl    = &screen_init_sdl;
    screen.getEvent    = &screen_getEvent;
    screen.adaptRender = &screen_adaptRender;
    screen.destroy     = &screen_destroy;
    screen.clear       = &screen_clear;

    return (screen);
}


/**
 *  FUNCTION TO INIT SDL_WINDOW AND SDL_RENDERER of the structure
 * 
 */
int screen_init_sdl(Screen *screen) {

    screen->m_window = SDL_CreateWindow(screen->m_titleWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen->m_widthWindow, screen->m_heightWindow, SDL_WINDOW_SHOWN);
    if (screen->m_window == NULL) {
        printf("probleme creation fenetre\n");
        return (EXIT_FAILURE);
    }

    screen->m_render = SDL_CreateRenderer(screen->m_window, -1, SDL_RENDERER_ACCELERATED);
    if (screen->m_render == NULL) {
        printf("probleme creation renderer\n");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}


/**
 * FUNCTION which destroy WINDOW and RENDERER of the Structure 
 * 
 */
void screen_destroy(Screen *screen) {
    SDL_DestroyRenderer(screen->m_render);
    SDL_DestroyWindow(screen->m_window);
}

/**
 * FUNCTION get the window size and apply the same size to the main render
 * 
 * 
 */
void screen_adaptRender(Screen *screen) {
    //get the window size into widthWindow and heightWindow
    SDL_GetWindowSize(screen->m_window, &screen->m_widthWindow, &screen->m_heightWindow);

    //set the render size at the window size
    SDL_RenderSetLogicalSize(screen->m_render, screen->m_widthWindow, screen->m_heightWindow);

}

/**
 * FUNCTION clear the screen in black
 * 
 * 
 */
void screen_clear(Screen *screen) {
    //set the black color of the renderer
    SDL_SetRenderDrawColor(screen->m_render, 0, 0, 0, 255);
    //apply the color to all renderer
    SDL_RenderClear(screen->m_render);

}

/**
 * FUNCTION get all event on the program
 * 
 * 
 */
void screen_getEvent(Screen *screen) {
    while (SDL_PollEvent(&screen->m_event)) {
        if (screen->m_event.type == SDL_QUIT) {
            screen->m_isRunning = 0;
        }
    }
}