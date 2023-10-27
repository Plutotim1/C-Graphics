#include "defs.h"
#include "colors.h"
#include "image_helper.h"


typedef struct Player {
    int health;
    int ammo;
    int speed;
    //what fraction of the Screen the player should take up
    int size_x;
    //the same
    int size_y;
    int x;
    int y;
} Player;


void do_input(void);
void init_player(void);
void render(App app);
void reset_screen(App app, Color color);
void set_draw_color(App app, Color color, int opacity);


bool shouldClose;
int pos;
Player player;


int main(void) {
    printf("foo\n");
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
    app.surface = SDL_GetWindowSurface(app.window);

    pos = 0;
    //start = clock();
    SDL_UnlockSurface(app.surface);

    printf("bar\n");

    //initialize the player with default values
    init_player();

    while(!shouldClose) {
        do_input();
        render(app);
        SDL_Delay(8);
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


void init_player(void) {
    Player p = {BASE_HP, BASE_AMMO, BASE_SPEED, SCREEN_WIDTH / BASE_PLAYER_SIZE_X, SCREEN_HEIGTH / BASE_PLAYER_SIZE_Y, SCREEN_WIDTH / 2, SCREEN_HEIGTH / 2};
    p.x -= p.size_x / 2;
    p.y -= p.size_y / 2;
    player = p;
}


void render(App app) {
    reset_screen(app, BLACK);
    SDL_Texture *text = load_texture(app.renderer,PLAYER_TEXTURE);
    if (text == NULL) {
        printf("%s\n", PLAYER_TEXTURE);
        exit(1);
    }
    SDL_Rect pos = {player.x, player.y, player.size_x, player.size_y};
    render_texture(app, text, &pos);
    SDL_RenderPresent(app.renderer);
}


void reset_screen(App app, Color color) {
    set_draw_color(app, color, 255);
    SDL_RenderFillRect(app.renderer, NULL);
}


void set_draw_color(App app, Color color, int opacity) {
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, opacity);
}





