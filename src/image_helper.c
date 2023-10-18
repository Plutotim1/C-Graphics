#include "image_helper.h"


SDL_Surface *load_texture_surface(char *filename) {
    SDL_Surface * surf = IMG_Load(filename);
    return surf;
}


void apply_texture_surface(App app, SDL_Surface *texture, int x, int y) {
    SDL_Rect target_rect = {x, y, texture->w, texture->h};
    SDL_BlitSurface(texture, NULL, app.surface, &target_rect);
}