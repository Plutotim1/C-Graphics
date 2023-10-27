#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdbool.h>


typedef struct App {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
} App;

SDL_Surface *load_texture_surface(const char *filename);
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *filename);
void render_texture_surface(App app, SDL_Surface *texture, int x, int y);
void render_texture(App app, SDL_Texture *texture, SDL_Rect *pos);