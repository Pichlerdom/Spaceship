#include"display.h"

#define __G 0.001

enum KEYS{W_KEY, A_KEY, S_KEY, D_KEY,R_KEY,F_KEY,V_KEY};

float scale = 1.0;
float time_scale=0.01;

void*
display_main(void * display_config){
	bool key_down[7];
	Vec points[1000];
	int points_first = 0;
	int count = 0;
	int spectator = 0;

	Display_Config* config = (Display_Config *) display_config;
	Ship ship;
	ship.mass = 2000;
	ship.pos.x = 0;
	ship.pos.y = 120;
	ship.orient.x = 0;
	ship.orient.y = -1;
	ship.dir.x = 9;
	ship.dir.y = 0;
	ship.thrust_level = 0;
	ship.thrust_max = 2;
	ship.angle = 0;
	ship.rotation_speed =4;

	PlanetArr *container = (PlanetArr *)calloc(1,sizeof(PlanetArr));
    container->planets = (Planet *)calloc(100,sizeof(Planet));
	container->count =100;


	Planet *planets = container->planets;

planets[0].mass = 10000000; 
	planets[0].radius = 200;
	planets[0].dir.x = 0;
	planets[0].dir.y = 0;
	planets[0].pos.x = 0;
	planets[0].pos.y = 0;

planets[1].mass = 500000; 
	planets[1].radius = 50;
	planets[1].dir.x = 0;
	planets[1].dir.y = -4;
	planets[1].pos.x = 600;
	planets[1].pos.y = 0;
planets[2].mass = 200000; 
	planets[2].radius = 70;
	planets[2].dir.x = 0;
	planets[2].dir.y = 3;
	planets[2].pos.x = -1000;
	planets[2].pos.y = 0;
	for(int i = 3; i < container->count;i++){
	planets[i].mass = 1000; 
	planets[i].radius = 1;
	planets[i].dir.x = rand()%500/100;
	planets[i].dir.y = rand()%500/100;
	planets[i].pos.x = rand()%200000/100 - 1000;
	planets[i].pos.y = rand()%200000/100 - 1000;
}

	uint32_t currTime = SDL_GetTicks();
	uint32_t frameTime = 0;
	Display *display = init_display();
	SDL_Event e;

	bool quit = false;
	while(!quit){
		currTime = SDL_GetTicks();		
		count ++;
		//event handling loop
		while(SDL_PollEvent(&e) != 0){

			switch(e.type){
			
				//close application
				case SDL_QUIT:
					quit = true;
				break;
				//mouse wheel events
				case SDL_MOUSEWHEEL:	
					if(e.wheel.y == 1){
						scale *= 1.1;
					}else if(e.wheel.y == -1){
						scale /= 1.1;
					}
				break;

				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_a: key_down[A_KEY] = true;
							break;
					case SDLK_d: key_down[D_KEY] = true;
							break;
					case SDLK_w: key_down[W_KEY] = true;
							break;
					case SDLK_s: key_down[S_KEY] = true;
							break;
					case SDLK_r: key_down[R_KEY] = true;
							break;
					case SDLK_f: key_down[F_KEY] = true;
							break;
					case SDLK_v: key_down[V_KEY] = true;
							break;
					
							break;
					}

				break;

				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
					case SDLK_a: key_down[A_KEY] = false;
							break;
					case SDLK_d: key_down[D_KEY] = false;
							break;
					case SDLK_w: key_down[W_KEY] = false;
							break;
					case SDLK_s: key_down[S_KEY] = false;
							break;
					case SDLK_r: key_down[R_KEY] = false;
							break;
					case SDLK_f: key_down[F_KEY] = false;
							break;
					case SDLK_v: key_down[V_KEY] = false;
							break;
					case SDLK_t: spectator ++;
							break;
					case SDLK_g: spectator --;
							break;
					}
				break;
			}
		}

		if(spectator == container->count)
		{

			display->pos.x = ship.pos.x;
			display->pos.y = ship.pos.y;
		}else if(spectator > container->count){
			spectator = 0;
			display->pos = planets[spectator].pos;	
		}else if(spectator < 0){
			spectator = container->count;
		}else{
			display->pos = planets[spectator].pos;
		}

		
		if(key_down[A_KEY]){
			rotate_Vec(&ship.orient, ship.rotation_speed);
			ship.angle += ship.rotation_speed;
			if(ship.angle >= 360){
				ship.angle = 0;
			}
		}
		if(key_down[D_KEY]){
			rotate_Vec(&ship.orient, -ship.rotation_speed);
			ship.angle -=ship.rotation_speed;
			if(ship.angle < 0){
				ship.angle = 359;
			}
		}	
		if(key_down[W_KEY]){
			ship.thrust_level += 1;
			if(ship.thrust_level >= 100)
			{
				ship.thrust_level = 100;
			}
			
		}
		if(key_down[S_KEY]){
			ship.thrust_level -= 4;
			if(ship.thrust_level <= 0)
			{
				ship.thrust_level = 0;
			}
		}
		if(key_down[R_KEY]){
			time_scale *= 1.05;
		}
		if(key_down[F_KEY]){
			time_scale /= 1.05;
		}
		if(key_down[V_KEY]){
			time_scale = 0.01;
		}
		printf("tscale: %f\t|| spectator: %d\n",time_scale,spectator);
		
		move_ship(&ship, container);
		if(count%3 == 0){
			points[points_first] = ship.pos;
			
			points_first++;
			if(points_first == 1000){
				points_first = 0;
			}
		}
		move_planets(container);
		


		//Clear screen
		SDL_SetRenderDrawColor( display->renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( display->renderer );
  
		draw_ship(&ship, display,ship.pos);
		draw_planets(display,container);
		for(int i = 0; i < 998; i ++){
			SDL_SetRenderDrawColor( display->renderer, 255, 0, 0, 0xFF );
			Vec p1,p2; 
			p1.x= points[i].x	/ scale + WINDOW_WIDTH/2.0   - display->pos.x  / scale;
			p1.y= points[i].y	/ scale + WINDOW_HEIGHT/2.0  - display->pos.y / scale;
			p2.x= points[i+1].x / scale + WINDOW_WIDTH/2.0  - display->pos.x  / scale;
			p2.y= points[i+1].y / scale + WINDOW_HEIGHT/2.0 - display->pos.y / scale;

			if(i != points_first-1){
				SDL_RenderDrawLine(	display->renderer,p1.x, p1.y,
								p2.x, p2.y);
			}
		}
		//Troust 
		SDL_Rect rect;
		rect.x = 10;
		rect.y = 110;
		rect.w = 7;
		rect.h = -ship.thrust_level;
		SDL_SetRenderDrawColor( display->renderer, 255, 0, 0, 0xFF );
		SDL_RenderFillRect(display->renderer, &rect);
		rect.x = 10;
		rect.y = 10 ;
		rect.w = 7;
		rect.h = 100;
		SDL_SetRenderDrawColor( display->renderer, 255, 255, 255, 0xFF );
		SDL_RenderDrawRect(display->renderer, &rect);
		
		//Update screen
		SDL_RenderPresent( display->renderer );
		
		print_ship(&ship);
		//FPS stuff
		frameTime = SDL_GetTicks() - currTime;
		if(frameTime > MS_PER_FRAME){
			frameTime = MS_PER_FRAME;
		}
		SDL_Delay(MS_PER_FRAME-frameTime);

	}

	
	return 0;
}
void move_ship(Ship *ship,PlanetArr *container){

	float dist = 0;
	float dx = 0;
	float dy = 0;

	Planet *planets = container->planets;
	//Ship
	for(int i = 0; i < container->count; i++){
		dx = ship->pos.x - planets[i].pos.x;
		dy = ship->pos.y - planets[i].pos.y;

		dist = sqrtf(dx * dx + dy * dy);

		dx /= dist;
		dy /= dist;

		float g = (__G *planets[i].mass)/(dist * dist);
		ship->dir.x -= dx * g *  time_scale;
		ship->dir.y -= dy * g *  time_scale;

		g =  (__G *ship->mass)/(dist * dist);
		planets[i].dir.x += dx * g *  time_scale;
		planets[i].dir.y += dy * g *  time_scale;

	}
	if(ship->thrust_level > 0){
		ship->dir.x += ship->orient.x * (ship->thrust_level/100) * ship->thrust_max*  time_scale;
		ship->dir.y += ship->orient.y * (ship->thrust_level/100) * ship->thrust_max*  time_scale;
	}
	ship->pos.x += ship->dir.x *  time_scale;
	ship->pos.y += ship->dir.y *  time_scale;
	

}

void draw_planets(Display *display, PlanetArr *container){
	for(int i = 0; i <  container->count; i++){
		Vec pos = container->planets[i].pos;
		Vec dir = container->planets[i].dir;
		float r = container->planets[i].radius;
		pos.x /= scale;
		pos.y /= scale;
		SDL_SetRenderDrawColor(display->renderer, 10, 255, 0, 0xFF);
		
		draw_planet(display, &pos, r / scale);
		
		if(container->planets[i].mass > 0){ 
			SDL_SetRenderDrawColor(display->renderer, 0xFF, 0x00, 0xFF, 0x55);
			
		}  
	}
}
void draw_planet(Display *display, Vec *pos, float r){
	int radius = r/2.0;
	pos->x -= display->pos.x / scale;//  + WINDOW_WIDTH/2.0;
	pos->y -= display->pos.y / scale;//+ WINDOW_HEIGHT/2.0;
	pos->x += WINDOW_WIDTH/2.0;
	pos->y += WINDOW_HEIGHT/2.0;
	
	SDL_RenderDrawPoint(display->renderer, pos->x, pos->y);
	if(pos->x > WINDOW_WIDTH || pos->y > WINDOW_HEIGHT ||
	   pos->x < 0 || pos->y < 0) return;

	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy*dy) <= ((radius) * (radius)) &&
				(dx*dx + dy*dy) > ((radius - 2) * (radius - 2)))
			{
				SDL_RenderDrawPoint(display->renderer, pos->x + dx, pos->y + dy);
			}
		}
	}
}

void move_planets(PlanetArr *container){
	float dist = 0;
	float dx = 0;
	float dy = 0;

	Planet *planets = container->planets;
	for(int i = 0; i < container->count - 1; i++){
		for(int j = i + 1; j < container->count; j++){
			dx = planets[j].pos.x- planets[i].pos.x;
			dy = planets[j].pos.y- planets[i].pos.y;

			dist = sqrtf(dx * dx + dy * dy);

			dx /= dist;
			dy /= dist;

			float g = (__G *planets[i].mass)/(dist * dist);
			planets[j].dir.x -= dx * g * time_scale;
			planets[j].dir.y -= dy * g * time_scale;

			g =  (__G * planets[j].mass)/(dist * dist);
			planets[i].dir.x += dx * g * time_scale;
			planets[i].dir.y += dy * g * time_scale;
		}
	}
	
	for(int i = 0; i < container->count; i++){
		planets[i].pos.x += planets[i].dir.x * time_scale;
		planets[i].pos.y += planets[i].dir.y * time_scale;

	}
}


void print_ship(Ship *ship){
	  printf("level: %.2f \t|| pos: %.2f, %.2f\n", ship->thrust_level, ship->pos.x, ship->pos.y);
	  printf("thrust: %.2f \t|| dir: %.2f, %.2f \t|| angle: %.1f\n",ship->thrust_max * (ship->thrust_level/100),ship->dir.x, ship->dir.y,ship->angle);
}

void draw_ship(Ship *ship, Display *display, Vec at){
	//Setting the actual draw color.
	SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	Vec ship_parts[3];
	ship_parts[0].x = 0          / scale;
	ship_parts[0].y = (1.0/-1.0)  / scale ;
	ship_parts[1].x = (1.0/ 5.0)  / scale;
	ship_parts[1].y = (1.0/ 5.0)  / scale;
	ship_parts[2].x = (1.0/-5.0)  / scale;
	ship_parts[2].y = (1.0/ 5.0)  / scale;
	
	rotate_Vec(&(ship_parts[0]),ship->angle);
	rotate_Vec(&(ship_parts[1]),ship->angle);
	rotate_Vec(&(ship_parts[2]),ship->angle);
	
	ship_parts[0].x += WINDOW_WIDTH/2  +(ship->pos.x-display->pos.x) / scale; 
	ship_parts[0].y += WINDOW_HEIGHT/2 +(ship->pos.y-display->pos.y) / scale;
	ship_parts[1].x += WINDOW_WIDTH/2  +(ship->pos.x-display->pos.x) / scale;
	ship_parts[1].y += WINDOW_HEIGHT/2 +(ship->pos.y-display->pos.y) / scale;
	ship_parts[2].x += WINDOW_WIDTH/2  +(ship->pos.x-display->pos.x) / scale;
	ship_parts[2].y += WINDOW_HEIGHT/2 +(ship->pos.y-display->pos.y) / scale;
	

	//Drawing the lines we want. (-1, 0), (0, 1), (1, 0)
	SDL_RenderDrawLine(display->renderer,ship_parts[0].x, ship_parts[0].y,
								ship_parts[1].x, ship_parts[1].y);
	SDL_RenderDrawLine(display->renderer,ship_parts[1].x, ship_parts[1].y,
								ship_parts[2].x, ship_parts[2].y);
	SDL_RenderDrawLine(display->renderer,ship_parts[2].x, ship_parts[2].y,
								ship_parts[0].x, ship_parts[0].y);

	SDL_SetRenderDrawColor(display->renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
}

 void rotate_Vec(Vec* vec,float alpha){
	Vec temp;
	float rad = alpha * M_PI / 180.0;
	temp.x = vec->x * cos(rad) - vec->y * sin(rad);
	temp.y = vec->x * sin(rad) + vec->y * cos(rad);
	
	*vec = temp; 
}

Display* init_display(){ 
	Display *display = (Display *) calloc(1, sizeof(Display));
	if(display == NULL){
		printf("Display could not be created!");
		return NULL;
	}
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	    
        return NULL;
	}

    display->window = SDL_CreateWindow("followPoint",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH,
                                       WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN);
    if(display->window == NULL) {
        printf("Unable to create Window! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }
	display->renderer = SDL_CreateRenderer( display->window, -1, SDL_RENDERER_ACCELERATED );
	if( display->renderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return NULL;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(display->renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 

    return display;
 
}

