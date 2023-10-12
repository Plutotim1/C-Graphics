#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "colors.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGTH 720


//structs
typedef struct App {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
} App;


void do_input(void);
void render(App app);
void reset_screen(App app, Color color);
void set_draw_color(App app, Color color, int opacity);


bool shouldClose;
int pos;


int main(void) {
    //clock_t start, end;
    shouldClose = false;

    Color white;
    white.r = white.g = white.b = 255;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL init error");
        return 1;
    }
    struct App app;
    app.window = SDL_CreateWindow("test", 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, 0);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

    pos = 0;
    //start = clock();
    while(!shouldClose) {
        do_input();
        render(app);
        SDL_Delay(16);
    }
    //end = clock();
    //printf("frames per second: %f", (double) 1 / ((double) ((end - start) / pos) / CLOCKS_PER_SEC));

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}


void do_input(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				shouldClose = true;
				break;

			default:
				break;
		}
	}
}


void render(App app) {

    //reset_screen(app, WHITE);
    set_draw_color(app, WHITE, 255);
    SDL_RenderClear(app.renderer);
    set_draw_color(app, BLUE, 255);
    struct SDL_Rect rect;
    rect.x = pos;
    rect.y = 0;
    rect.w = 300;
    rect.h = SCREEN_HEIGTH;
    SDL_RenderFillRect(app.renderer, &rect);
    pos++;
    SDL_RenderPresent(app.renderer);
}


void reset_screen(App app, Color color) {
    set_draw_color(app, WHITE, 255);
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGTH; j++) {
            SDL_RenderDrawPoint(app.renderer, i, j);
        } 
    }
    //SDL_RenderDrawRect(app.renderer, NULL);
}


void set_draw_color(App app, Color color, int opacity) {
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, opacity);
}





