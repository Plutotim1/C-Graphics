

#include "defs.h"
#include "colors.h"
#include "image_helper.h"


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
    reset_screen(app, WHITE);
    //test
    SDL_Surface *text = load_texture_surface(PLAYER_TEXTURE);
    apply_texture_surface(app, text, pos, SCREEN_HEIGTH / 2);
    pos++;
    SDL_RenderPresent(app.renderer);
}


void reset_screen(App app, Color color) {
    SDL_RenderDrawRect(app.renderer, NULL);
}


void set_draw_color(App app, Color color, int opacity) {
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, opacity);
}





