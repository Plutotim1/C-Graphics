#include "defs.h"
#include "colors.h"
#include "image_helper.h"


typedef struct Player {
    int health;
    int ammo;
    int speed;
    SDL_Rect pos;
} Player;


typedef struct Projectile {
    int damage;
    int speed;
    SDL_Rect pos;
} Projectile;


typedef struct Projectile_List {
    Projectile *projectile;
    struct Projectile_List *previous;
    struct Projectile_List *next;
} Projectile_List;


typedef struct List_Start {
    Projectile_List *first;
    int length;
}   List_Start;


//checks wether a key is currently held down
typedef struct Keys {
    bool a_key;
    bool d_key;
    bool s_key;
    bool w_key;
} Keys;


void exit(int code);
void check_input(void);
void handle_key_event(SDL_KeyboardEvent event, bool press);
void handle_movement(void);
void init_player(void);
void render(App app);
void render_projectile(Projectile *projectile, App app);
void reset_screen(App app, Color color);
void set_draw_color(App app, Color color, int opacity);
void create_projectile();


bool shouldClose;
Player player;
Keys keys;
struct List_Start projectiles;


int main(void) {
    //uncomment to measure framerate
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

    //uncomment to measure framerate
    //start = clock();
    SDL_UnlockSurface(app.surface);


    //initialize all keys as not pressed
    Keys k = {false, false, false, false};
    keys = k;


    //initialize the player with default values
    init_player();

    //initialize projectile as none
    projectiles.length = 0;
    projectiles.first = NULL;

    while(!shouldClose) {
        check_input();
        handle_movement();
        render(app);
        SDL_Delay(8);
    }
    //uncomment to measure framerate
    //end = clock();
    //printf("frames per second: %f", (double) 1 / ((double) ((end - start) / pos) / CLOCKS_PER_SEC));

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}


void quit_programm(int code) {
    exit(code);
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
        
        case SDLK_SPACE:
            if (event.repeat == 0 && press == true) {
                create_projectile();
            }
            break;
        
        default:
            break;
    }
}


void handle_movement(void) {
    if (keys.w_key) {
        player.pos.y -= player.speed;
    }
    if (keys.s_key) {
        player.pos.y += player.speed;
    }
    if (keys.a_key) {
        player.pos.x -= player.speed;
    }
    if (keys.d_key) {
        player.pos.x += player.speed;
    }

    //check wether the player is out of bounds
    if (player.pos.x < 0) {
        player.pos.x = 0;
    }
    if (player.pos.y < 0) {
        player.pos.y = 0;
    }
    if (player.pos.x > (SCREEN_WIDTH - player.pos.w)) {
        player.pos.x = SCREEN_WIDTH - player.pos.w;
    }
    if (player.pos.y > (SCREEN_HEIGTH - player.pos.h)) {
        player.pos.y = SCREEN_HEIGTH - player.pos.h;
    }

    //move projectiles depending on their speed (1 pixel per speed)
    Projectile_List *pl = projectiles.first;

    //pointer used to be able to free list items
    Projectile_List *free_pointer;

    //iterate over projectiles
    while(pl != NULL) {
        //move projectile
        pl->projectile->pos.y -= pl->projectile->speed;

        //check wether the projectile is out of bounds
        if (pl->projectile->pos.y > SCREEN_HEIGTH || pl->projectile->pos.y < 0) {

            //remove the projectile from the list

            //if it has a previous and next, connect those together
            if (pl->previous != NULL && pl->next != NULL) {
                pl->previous->next = pl->next;
                pl->next->previous = pl->previous;
            }
            if (pl->next != NULL && pl->previous ==NULL){
                pl->next->previous = NULL;
                projectiles.first = pl->next;
            }
            if (pl->next == NULL && pl->previous == NULL) {
                projectiles.first = NULL;
            }
            if (pl->next == NULL && pl->previous != NULL) {
                pl->previous->next = NULL;
            }
            //free_pointer = pl;
            pl = pl->next;
            //free(free_pointer);
        }
        else {
            pl = pl->next;
        }
    }
}


void init_player(void) {
    SDL_Rect rect = { SCREEN_WIDTH / 2, SCREEN_HEIGTH / 2, SCREEN_WIDTH / BASE_PLAYER_SIZE_X, SCREEN_HEIGTH / BASE_PLAYER_SIZE_Y};
    Player p = {BASE_HP, BASE_AMMO, BASE_SPEED, rect};
    p.pos.x -= p.pos.w / 2;
    p.pos.y -= p.pos.h / 2;
    player = p;
}


void create_projectile() {
    //malloc memory
    Projectile_List *pl = malloc(sizeof(Projectile_List));
    Projectile *p = malloc(sizeof(Projectile));


    //check for errors
    if (pl == NULL || p == NULL) {
        printf("ERROR: couldn't allocate memory for a projectile");
        quit_programm(1);
    }

    //calculate size
    //TODO check wether size is larger thanh screen heigth
    int s = SCREEN_WIDTH / BASE_PROJECTILE_SIZE;

    //calculate position
    int x = player.pos.x + player.pos.w / 2 - s / 2;
    int y = player.pos.y + player.pos.h / 2 - s / 2;
    
    //initialize position rectangle values
    SDL_Rect pos = {x, y, s, s};

    //initialize projectile values
    p->damage = BASE_PROJECTILE_DAMAGE;
    p->speed = BASE_PROJECTILE_SPEED;
    p->pos = pos;

    //assign projectile
    pl->projectile = p;

    //initialize projectile list
    pl->previous = NULL;
    pl->next = projectiles.first;
    if (pl ->next != NULL) {
        pl->next->previous = pl;
    }
    projectiles.first = pl;

    projectiles.length++;
}


void render(App app) {
    reset_screen(app, BLACK);

    //get player texture
    SDL_Texture *text = load_texture(app.renderer, PLAYER_TEXTURE);
    if (text == NULL) {
        printf("couldn'*t find player texture at the following location: %s\n", PLAYER_TEXTURE);
        quit_programm(1);
    }

    //render player
    render_texture(app, text, &(player.pos));

    //check if there is a projectile
    if (projectiles.first == NULL) {
        SDL_RenderPresent(app.renderer);
        return;
    }

    //render projectiles

    Projectile_List *pl = projectiles.first;
    //load texture
    SDL_Texture *proj_text = load_texture(app.renderer, PROJECTILE_TEXTURE);
    //check for error
    if (proj_text == NULL) {
        printf("couldn't find projectile texture at the following location: %s\n", PROJECTILE_TEXTURE);
        quit_programm(1);
    }
    //iterate over projectiles
    while(pl != NULL) {
        //render projectile
        render_texture(app, proj_text, &(pl->projectile->pos));

        pl = pl->next;
    }

    SDL_RenderPresent(app.renderer);
}


void reset_screen(App app, Color color) {
    set_draw_color(app, color, 255);
    SDL_RenderFillRect(app.renderer, NULL);
}


void set_draw_color(App app, Color color, int opacity) {
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, opacity);
}





