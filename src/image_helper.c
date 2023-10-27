#include "image_helper.h"


SDL_Surface *load_texture_surface(const char *filename) {
    SDL_Surface * surf = IMG_Load(filename);
    return surf;
}


SDL_Texture *load_texture(SDL_Renderer *renderer, const char *filename) {
    return IMG_LoadTexture(renderer, filename);
}


void render_texture_surface(App app, SDL_Surface *texture, int x, int y) {
    SDL_Rect target_rect = {x, y, 0, 0};
    SDL_BlitSurface(texture, NULL, app.surface, NULL);
}


void render_texture(App app, SDL_Texture *texture, SDL_Rect *pos) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
    SDL_RenderCopy(app.renderer, texture, NULL, pos);
}