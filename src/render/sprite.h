#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "geometry.h"
#include "screen.h"

class Sprite
{
   public:
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    int m_width;
    int m_height;

    Sprite();
    Sprite(const char* png_path, Screen* screen);
    ~Sprite();

    void render(PixelPosition position, Screen* screen);
};

#endif
