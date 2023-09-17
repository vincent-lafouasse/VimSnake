#ifndef __RENDER_H__
#define __RENDER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define HEIGHT 600
#define WIDTH 800

class Screen
{
   public:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Screen(void);
    ~Screen(void);

    void show(void);
};

class Sprite
{
   public:
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    int m_width;
    int m_height;

    Sprite(const char* png_path, Screen* screen);
    ~Sprite();

    void render(int x, int y, Screen* screen);
};

#endif
