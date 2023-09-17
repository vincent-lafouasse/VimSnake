#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Screen
{
   public:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Screen(int width, int height);
    ~Screen(void);

    void show(void);
};

#endif
