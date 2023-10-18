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

SDL_Texture *load_texture(SDL_Renderer *renderer, char *filename);
void apply_texture_surface(App app, SDL_Surface *texture, int x, int y);