#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#include <SDL2/SDL.h>
#include "spaceship.h"
#include "display.h"

#define PLANETS_NUMBER 23
#define __DIST 1
#define __M_MAX 200000
#define __M_MIN 100000
#define __R_MIN 1
#define __R_MAX 100
#define __SEEDMASS 10000
#define __MOVE 1
#define __SIZE 2000.0



int main(int argc, char* argv[]){
	pthread_t display_thread;
	pthread_create(&display_thread, NULL,display_main, NULL);

	pthread_join(display_thread,NULL);
	return 0;
}



