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


//checks wether a key is currently held down
typedef struct Keys {
    bool a_key;
    bool d_key;
    bool s_key;
    bool w_key;
} Keys;


void check_input(void);
void handle_key_event(SDL_KeyboardEvent event, bool press);
void handle_movement(void);
void init_player(void);
void render(App app);
void reset_screen(App app, Color color);
void set_draw_color(App app, Color color, int opacity);


bool shouldClose;
Player player;
Keys keys;


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

    //start = clock();
    SDL_UnlockSurface(app.surface);

    printf("bar\n");

    //initialize all keys as not pressed
    Keys k = {false, false, false, false};
    keys = k;


    //initialize the player with default values
    init_player();

    while(!shouldClose) {
        check_input();
        handle_movement();
        render(app);
        SDL_Delay(8);
    }
    //end = clock();
    //printf("frames per second: %f", (double) 1 / ((double) ((end - start) / pos) / CLOCKS_PER_SEC));

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}


void check_input(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
			case SDL_QUIT:
				shouldClose = true;
				break;

            case SDL_KEYDOWN:
                handle_key_event(event.key, true);
                break;

            case SDL_KEYUP:
                handle_key_event(event.key, false);
                break;


			default:
				break;
		}
	}
}


void handle_key_event(SDL_KeyboardEvent event, bool press) {
    switch (event.keysym.sym) {
        case SDLK_w:
            keys.w_key = press;
            break;
        case SDLK_a:
            keys.a_key = press;
            break;
        case SDLK_s:
            keys.s_key = press;
            break;
        case SDLK_d:
            keys.d_key = press;
            break;
        
        default:
            break;
    }
}


void handle_movement(void) {
    if (keys.w_key) {
        player.y -= player.speed;
    }
    if (keys.s_key) {
        player.y += player.speed;
    }
    if (keys.a_key) {
        player.x -= player.speed;
    }
    if (keys.d_key) {
        player.x += player.speed;
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





