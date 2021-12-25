#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>

typedef struct Screen Screen;       //prototype de la structure

//------PROTOTYPES-----------------------------------------
Screen      screen_init(int w, int h, char *title);                      //the initialization of the struct
int         screen_init_sdl(Screen *screen);       //the initialization of the sdl element of the struct
void        screen_clear(Screen *screen);          //clear the screen
void        screen_adaptRender(Screen *screen);    //adapt the render of the window size
void        screen_getEvent(Screen *screen);       //get event of the program
void        screen_destroy(Screen *screen);        //destroy sdl element of the struct
//---------------------------------------------------------


struct Screen {
    SDL_Window      *m_window;      //the window
    SDL_Renderer    *m_render;      //the render
    SDL_Event       m_event;        //the event of the program
    int             m_widthWindow;  //the width of the window
    int             m_heightWindow; //the height of the window
    float           m_ratioScreenBegin;  //the ratio of the window size
    char            *m_titleWindow; //the title of the window
    int             m_isRunning;    //the state of the while loop


    int             (*init_sdl)(Screen *screen);   //pointer of function screen_init_sdl
    void            (*clear)(Screen *screen);      //pointer of function screen_clear
    void            (*adaptRender)(Screen *screen);//pointer of funtion screen_adaptRender
    void            (*getEvent)(Screen *screen);   //pointer of function screen_getEvent
    void            (*destroy)(Screen *screen);    //pointer of function screen_destroy

};


#endif