#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "spaceship.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

#define FPS 33
#define MS_PER_FRAME 1000/FPS

typedef struct{
	SDL_Renderer* renderer;
	SDL_Window* window;
	Vec pos;
}Display;


typedef struct{
	int width;
 	int height;
	int fps;
}Display_Config;


void*
display_main(void * display_config);

Display* init_display();


void move_ship(Ship *ship,PlanetArr *container);
void draw_ship(Ship *ship,Display *display#,Vec at);
void print_ship(Ship *ship);


void draw_planets(Display *display, PlanetArr *container);
	
void draw_planet(Display *display, Vec *pos, float r);
void move_planets(PlanetArr *container);
 void rotate_Vec(Vec* vec,float alpha);
#endif
